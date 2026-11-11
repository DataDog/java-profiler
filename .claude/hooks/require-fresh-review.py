#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Claude Code PreToolUse hook: block commands that mention `gh pr create|new|ready`
while the branch's review marker is stale, `gh pr create` whose title and body
reference no ticket, and `gh pr ready` whose PR description was last edited before
the PR's head commit. A single plain `gh pr create|new|ready` call that certainly targets
another repository than this one is not gated. Pushes are gated by .githooks/pre-push."""

import json
import os
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime
import re
import shlex
import subprocess
import sys

# Matched on raw text, not parsed: subshells, `bash -c`, if/then and multi-line
# commands cannot hide it. The cost is a false block when the text is only quoted.
PR_CMD = re.compile(r"\bgh\b[^\n]*?\bpr\s+(create|new|ready)\b([^\n;&|)]*)")
# Anything that can point gh or git at another checkout than the payload cwd.
DIR_CHANGE = re.compile(r"(^|[\s;&|(){}])(cd|pushd|popd)(\s|$)|\bGIT_(DIR|WORK_TREE)="
                        r"|\benv\b[^\n;&|]*\s(-C|--chdir)\b", re.M)
# The hook runs before the command, so a git step that moves HEAD in the same command
# would be judged on the pre-command state.
GIT_STATE_CHANGE = re.compile(r"\bgit\b[^\n;&|]*?\s(commit|switch|checkout|rebase|reset|"
                              r"merge|cherry-pick|am|pull|revert|stash|restore)\b")
# What an exempted command must spell its target as: no host aliases or other forms.
OWNER_REPO = re.compile(r"[\w.-]+/[\w.-]+")
PR_URL = re.compile(r"https://github\.com/([\w.-]+/[\w.-]+)/pull/\d+/?")
# Every character an exempted command may contain. Anything else (\r, \, expansions, operators)
# might split differently in bash than in shell_words, so it keeps the command gated.
PLAIN_COMMAND = re.compile(r"[A-Za-z0-9 ._:/=@'\",+-]+")
# The repository this gate protects, whatever the checkout's remotes point at.
PROTECTED_REPO = "datadog/java-profiler"
REMOTE_URL = re.compile(r"(?:https://|ssh://git@|git@)github\.com[:/]([\w.-]+/[\w.-]+?)(?:\.git)?/?")
TRUSTED_REF = "refs/remotes/origin/main"  # qualified: a tag named origin/main must not win
# git_out and the trusted-ref loading are copied in require-fresh-review.py,
# require-gradle-wrapper.py and protect-knowledgebase.py; change all three together.
HEAD_FLAG = re.compile(r"(^|\s)(--head\b|-H)")
BASE_FLAG = re.compile(r"(?:^|\s)(?:--base[= ]\s*|-B\s*)(['\"]?)([^\s'\"]+)\1")


def git_out(args, cwd):
    res = subprocess.run(["git", *args], cwd=cwd, stdout=subprocess.PIPE,
                         stderr=subprocess.DEVNULL)
    return res.stdout.decode(errors="replace").strip() if res.returncode == 0 else None


def words(text):
    try:
        return shlex.split(text)
    except ValueError:
        return text.split()


def gh_query(args, cwd):
    """stdout of a gh query, or None when gh, network or auth fails."""
    try:
        res = subprocess.run(["gh", *args], cwd=cwd, stdout=subprocess.PIPE,
                             stderr=subprocess.DEVNULL, timeout=10)
    except (OSError, subprocess.TimeoutExpired):
        return None
    out = res.stdout.decode().strip()
    return out if res.returncode == 0 and out else None


def origin(name):
    return name if name.startswith("origin/") else "origin/" + name


def repo_flag(tokens):
    """Value of -R/--repo in any of gh's spellings (`-R x`, `-Rx`, `--repo x`, `--repo=x`)."""
    for i, t in enumerate(tokens):
        if t in ("-R", "--repo"):
            return tokens[i + 1] if i + 1 < len(tokens) else None
        if t.startswith("--repo="):
            return t[len("--repo="):]
        if t.startswith("-R") and len(t) > 2:
            return t[2:]
    return None


def ready_target(args, repo, cwd):
    """(PR number, check arguments) for the PR `gh pr ready` targets, from GitHub so the
    commits the PR holds are checked; ("", []) means the current branch, None that it
    cannot be resolved."""
    selector = pr_selector(args)
    out = gh_query(["pr", "view", *selector[:1], *(["-R", repo] if repo else []), "--json",
                    "number,headRefName,headRefOid,baseRefName", "-q",
                    '"\\(.number) \\(.headRefName) \\(.headRefOid) \\(.baseRefName)"'], cwd)
    if not out or len(out.split()) != 4:
        return None if selector else ("", [])
    number, head, oid, base = out.split()
    return number, ["--branch", head, "--commit", oid, "--base", origin(base)]


# `gh pr create` flags that take a value, plus the global -R; short form -> long form.
VALUE_FLAGS = {"-t": "--title", "-b": "--body", "-F": "--body-file", "-B": "--base",
               "-H": "--head", "-r": "--reviewer", "-a": "--assignee", "-l": "--label",
               "-p": "--project", "-m": "--milestone", "-T": "--template", "-R": "--repo",
               "--recover": "--recover"}
FILL_FLAGS = ("-f", "--fill", "--fill-first", "--fill-verbose")
# The only valueless tokens the text is judged with. Anything else (--web, --editor,
# --dry-run in any spelling, a combined short flag, a stray word) makes the text unknown.
JUDGED_FLAGS = FILL_FLAGS + ("-d", "--draft")


def parse_flags(tokens):
    """({long flag: [values]}, {other flags}) in pflag syntax (`--x v`, `--x=v`, `-x v`,
    `-xv`); a value is never read as a flag. None when a value flag has no value."""
    values, others, i = {}, set(), 0
    while i < len(tokens) and tokens[i] != "--":
        t = tokens[i]
        long = None
        if t.startswith("--"):
            name, attached, value = t.partition("=")
            if name in VALUE_FLAGS.values():
                long = name
        elif t[:2] in VALUE_FLAGS:
            long, value = VALUE_FLAGS[t[:2]], t[2:]
            attached = value
        if long is None:
            others.add(t)
        else:
            if not attached:
                i += 1
                if i == len(tokens):
                    return None
                value = tokens[i]
            values.setdefault(long, []).append(value)
        i += 1
    return values, others


def last(values):
    return values[-1] if values else None


def autofill(cwd, base, mode):
    """(title, body) that gh's `mode` fill flag derives from the commits since `base`: one
    commit or --fill-first gives the first commit's subject and body; several give the
    branch name with `-`/`_` as spaces and the subjects, plus bodies for --fill-verbose."""
    # gh lists `log --cherry base...head`: no merges, patch-equivalent commits kept.
    log = git_out(["log", "--reverse", "--right-only", "--no-merges", "--format=%s%x00%b%x01",
                   "refs/remotes/%s...HEAD" % base], cwd)
    commits = [c.lstrip("\n").split("\0", 1) for c in (log or "").split("\1") if c.strip()]
    if not commits:
        return None
    if len(commits) == 1 or mode == "--fill-first":
        return commits[0][0], commits[0][1]
    branch = git_out(["symbolic-ref", "--quiet", "--short", "HEAD"], cwd)
    if branch is None:
        return None
    verbose = mode == "--fill-verbose"
    return re.sub("[-_]", " ", branch), "\n".join(s + ("\n" + b if verbose else "")
                                                  for s, b in commits)


def shell_words(text):
    """`text` split into shell words, with each unquoted operator, redirection and newline
    as its own token; None when the quoting does not parse."""
    try:
        lexer = shlex.shlex(text, posix=True, punctuation_chars="();<>|&\n")
        lexer.whitespace = " \t\r"
        lexer.commenters = ""
        lexer.whitespace_split = True
        return list(lexer)
    except ValueError:
        return None


def foreign_target(command, top):
    """OWNER/REPO, lowercase, of another repository that `command` (as typed) certainly
    targets: one plain `gh [-R R] pr create|new|ready` call whose target and remotes are
    spelled strictly (utils/README.md). None whenever that is not certain."""
    if not PLAIN_COMMAND.fullmatch(command):
        return None
    tokens = shell_words(command)
    # PLAIN_COMMAND already rules out operators, redirections and comments.
    if not tokens or tokens[0] != "gh" or "--" in tokens or "" in tokens or \
            any(re.match(r"-[^-]{2}", t) for t in tokens):
        return None
    values, positional, i = {}, [], 1
    while i < len(tokens):
        t = tokens[i]
        name, eq, value = t.partition("=")
        if not t.startswith("-"):
            positional.append(t)
        elif eq and name in VALUE_FLAGS.values():
            values.setdefault(name, []).append(value)
        elif (t in VALUE_FLAGS or t in VALUE_FLAGS.values()) and i + 1 < len(tokens):
            i += 1
            values.setdefault(VALUE_FLAGS.get(t, t), []).append(tokens[i])
        elif t not in JUDGED_FLAGS:
            return None  # a flag this list lacks might take the next word as its value
        i += 1
    if positional[:1] != ["pr"] or len(positional) < 2 or \
            positional[1] not in ("create", "new", "ready"):
        return None
    selectors = positional[2:]
    if positional[1] == "ready" and selectors and "/" in selectors[0]:
        url = PR_URL.fullmatch(selectors[0]) if len(selectors) == 1 else None
        target = url.group(1) if url else None  # gh takes a PR URL's repository over -R
    else:
        repos = values.get("--repo", [])
        target = repos[0] if len(repos) == 1 and OWNER_REPO.fullmatch(repos[0]) else None
    if target is None:
        return None
    # Every fetch and push URL git uses, after url.<base>.insteadOf/pushInsteadOf.
    urls = [u for r in (git_out(["remote"], top) or "").split()
            for args in (["--all"], ["--push", "--all"])
            for u in (git_out(["remote", "get-url", *args, r], top) or "").splitlines()]
    remotes = [REMOTE_URL.fullmatch(u) for u in urls]
    if not remotes or not all(remotes):
        return None
    names = {m.group(1).lower() for m in remotes} | {PROTECTED_REPO}
    target = target.lower()
    if target in names or target.split("/")[1] in {n.split("/")[1] for n in names}:
        return None
    # A fork network shares its root (GitHub's `source`), also across renames and transfers.
    with ThreadPoolExecutor() as pool:
        roots = list(pool.map(lambda name: network_root(name, top), [target] + sorted(names)))
    if not all(roots) or roots[0] in roots[1:]:
        return None  # a failed lookup, or the same fork network
    return target


def pr_selector(args):
    """The positional PR selectors of a `gh pr` subcommand: words no flag ate."""
    return [a for i, a in enumerate(args)
            if not a.startswith("-") and (i == 0 or args[i - 1] not in ("-R", "--repo"))]


def gh_time(text):
    """gh's ISO 8601 timestamp ("...Z") as an aware datetime, or None when unparseable
    or missing a UTC designator (a naive value would crash the aware-vs-aware comparison)."""
    try:
        dt = datetime.fromisoformat(text.replace("Z", "+00:00"))
    except ValueError:
        return None
    return None if dt.tzinfo is None else dt


PR_TIMES_QUERY = ('query($o:String!,$n:String!,$p:Int!){repository(owner:$o,name:$n){'
                  'pullRequest(number:$p){lastEditedAt createdAt'
                  ' commits(last:1){nodes{commit{committedDate}}}}}}')


def pr_repo(repo, cwd):
    """OWNER/NAME of the repository the PR belongs to: a full -R name as given, otherwise
    resolved from the checkout (or gh's own resolution of a bare -R name). None when
    unresolvable."""
    if repo and re.fullmatch(r"[^/]+/[^/]+", repo):
        return repo
    return gh_query(["repo", "view", *(["-R", repo] if repo else []), "--json",
                     "nameWithOwner", "-q", ".nameWithOwner"], cwd)


def stale_description(number, repo, cwd):
    """True when the PR body was last edited before its head commit, so it may predate
    the latest code. GitHub's updatedAt also moves on comments and on pushed commits, so
    it cannot date the description: the body's own timestamps are compared (lastEditedAt,
    createdAt fallback). The head commit's date is fetched directly -- commits is a
    paginated connection and only its first page is returned, so .[-1] over it can pick
    a non-head commit. None (fail open) when gh fails, the PR has no commits, or a
    timestamp is unparseable."""
    full = pr_repo(repo, cwd)
    if not full or "/" not in full or not number.isdigit():
        return None
    owner, _, name = full.partition("/")
    out = gh_query(["api", "graphql", "-f", "query=" + PR_TIMES_QUERY,
                    "-f", "o=" + owner, "-f", "n=" + name, "-F", "p=" + number,
                    "--jq",
                    '(.data.repository.pullRequest) as $p | '
                    '(($p.lastEditedAt // $p.createdAt) // "") + " "'
                    ' + ($p.commits.nodes[0].commit.committedDate // "")'], cwd)
    times = [gh_time(part) for part in (out or "").split()]
    if len(times) != 2 or None in times:
        return None
    return times[0] < times[1]


def network_root(name, top):
    """OWNER/REPO, lowercase, of the root of `name`'s fork network as GitHub resolves it
    (the repository itself when it is not a fork); None when gh fails."""
    out = gh_query(["api", "repos/" + name, "--jq", '.source.full_name // .full_name'], top)
    return out.lower() if out else None


def pr_text(rest, cwd):
    """The title and body `gh pr create` will use, or None when unsure (CI checks those).
    Only a simple command with literal values is judged; as in gh, the last flag wins,
    --body-file beats --body, and explicit values beat a fill flag."""
    tokens = shell_words(rest)
    if tokens is None:
        return None
    # The command ends at any unquoted operator, redirection, newline or comment. A quoted
    # value that looks like one also ends it, and parse_flags then reports the missing value.
    for i, t in enumerate(tokens):
        if set(t) <= set("();<>|&\n") or t.startswith("#"):
            # shlex splits `2>&1` into "2", ">&", "1": the fd number is not an argument.
            fd = i > 0 and t[:1] in "<>" and tokens[i - 1].isdigit()
            tokens = tokens[:i - 1 if fd else i]
            break
    parsed = parse_flags(tokens)
    if parsed is None:
        return None
    values, others = parsed
    if others - set(JUDGED_FLAGS) or "--recover" in values:
        return None
    title = last(values.get("--title"))
    body = last(values.get("--body"))
    body_file = last(values.get("--body-file"))
    if body_file is not None:
        try:  # also `-` (stdin): no such file, so the text is unknown
            with open(os.path.join(cwd, body_file), errors="replace") as f:
                body_text = f.read()
        except OSError:
            return None
    # The shell expands `$`/backticks before gh runs; file and commit text is literal.
    if any("$" in v or "`" in v for v in (title or "", "" if body_file else body or "")):
        return None
    if body_file is not None:
        body = body_text
    fills = others & set(FILL_FLAGS)
    if len(fills) > 1:
        return None
    if fills and (title is None or body is None):
        base = last(values.get("--base")) or configured_base(cwd)
        base = origin(base) if base else default_base(cwd)
        filled = autofill(cwd, base, fills.pop()) if base else None
        if filled is None:
            return None
        title = filled[0] if title is None else title
        body = filled[1] if body is None else body
    if title is None or body is None:
        return None
    return title + "\n" + body


def ticket_reason(top, cwd, rest):
    """None when the PR text references a ticket or cannot be known, else the block reason.
    Uses origin/main's .github/scripts/check_pr_ticket.py, the script CI runs."""
    source = git_out(["show", TRUSTED_REF + ":.github/scripts/check_pr_ticket.py"], top)
    text = pr_text(rest, cwd)
    if source is None or text is None:
        return None
    env = {**os.environ, "PR_TITLE": text, "PR_BODY": "", "PR_AUTHOR": ""}
    res = subprocess.run([sys.executable, "-I", "-c", source], cwd=top, env=env,
                         stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    if res.returncode != 1:
        return None
    return "the PR title and body reference no ticket. Add a Jira key (PROF-<n>) or a " \
           "GitHub issue (#<n>), e.g. in the template's JIRA line; CI checks the same."


def run_check(source, cwd, extra):
    # -I keeps the checkout root off sys.path, so planted stdlib-named files are not imported.
    return subprocess.run([sys.executable, "-I", "-c", source, "check", *extra], cwd=cwd,
                          stdout=subprocess.PIPE, stderr=subprocess.PIPE)


def configured_base(cwd):
    """`branch.<current>.gh-merge-base`, which bare `gh pr create` prefers to the repo default."""
    ref = git_out(["symbolic-ref", "--quiet", "HEAD"], cwd)
    if not ref:
        return None
    return git_out(["config", "--get", "branch.%s.gh-merge-base" % ref[len("refs/heads/"):]], cwd)


def create_base(command, cwd):
    """(base, error) for `gh pr create`: its --base, else the branch's gh-merge-base, else
    None for the repo default; error when the command names several bases."""
    bases = {origin(m.group(2)) for m in BASE_FLAG.finditer(command)}
    if len(bases) > 1:
        return None, "the command names several bases (%s)." % ", ".join(sorted(bases))
    base = bases.pop() if bases else configured_base(cwd)
    return (origin(base) if base else None), None


def default_base(cwd):
    """origin/<the repo's default branch> from GitHub, or None when gh fails."""
    default = gh_query(["repo", "view", "--json", "defaultBranchRef", "-q",
                        ".defaultBranchRef.name"], cwd)
    return origin(default) if default else None


def evaluate(source, cwd, sub, args, command, match_text):
    """Return None to allow, else the reason to block."""
    if sub == "ready":
        # The repo flag may sit before `pr` (`gh -R o/r pr ready`), so read it from the whole match.
        target = ready_target(args, repo_flag(words(match_text)), cwd)
        if target is None:
            return "cannot resolve the PR's head commit (gh failed); retry when gh works."
        number, extra = target
    else:
        if HEAD_FLAG.search(command):
            return "--head names a branch other than the checkout's.\n" \
                   "Run `gh pr create` from that branch's worktree without --head."
        base, error = create_base(command, cwd)
        if error:
            return error
        extra = ["--base", base] if base else []
    res = run_check(source, cwd, extra)
    if res.returncode == 0 and sub == "create" and not extra:
        # Only a passing check pays for the default-branch lookup.
        default = default_base(cwd)
        if default:
            res = run_check(source, cwd, ["--base", default])
    if res.returncode == 0 and sub == "ready":
        stale = stale_description(number, repo_flag(words(match_text)), cwd)
        if stale:
            return "the PR description was last edited before the PR's head commit and " \
                   "may not match the pushed code. Re-verify the title and description " \
                   "against the current diff, update or re-save it, then retry."
    if res.returncode == 0:
        return None
    reason = res.stderr.decode(errors="replace").strip()
    if res.returncode == 1:
        return "%s\nRun the pre-pr-review skill, then retry." % reason
    return "cannot check the review marker: %s\nRerunning the review will not help." % reason


def main():
    try:
        payload = json.load(sys.stdin)
    except ValueError:
        return 0
    # Join backslash-continued lines so `gh pr \<newline> create` is one line to the regexes.
    typed = payload.get("tool_input", {}).get("command", "")
    command = typed.replace("\\\n", " ")
    matches = list(PR_CMD.finditer(command))
    if not matches:
        return 0
    project = os.environ.get("CLAUDE_PROJECT_DIR") or os.getcwd()
    top = git_out(["rev-parse", "--show-toplevel"], payload.get("cwd") or os.getcwd())
    common = top and git_out(["rev-parse", "--path-format=absolute", "--git-common-dir"], top)
    if not common or common != git_out(["rev-parse", "--path-format=absolute",
                                        "--git-common-dir"], project):
        return 0  # another repository, or not a git checkout: not this repo's policy
    # origin/main's script, never the checkout's: the branch may be untrusted (a fork PR).
    source = git_out(["show", TRUSTED_REF + ":utils/review-marker.py"], top)
    if source is None:
        return 0  # the gate is not on the default branch yet
    if foreign_target(typed, top):
        return 0  # a PR in another repository: not this repo's policy
    for m in matches:
        sub = "create" if m.group(1) == "new" else m.group(1)
        args = words(m.group(2))
        if sub == "ready" and "--undo" in args:
            continue
        if DIR_CHANGE.search(command):
            reason = "the command may act on another checkout (cd, pushd, env -C or " \
                     "GIT_DIR).\nRun `gh pr %s` from the branch's worktree without it." % sub
        elif GIT_STATE_CHANGE.search(command):
            reason = "the command also changes git state (commit, switch, rebase, ...), " \
                     "which the check cannot see beforehand.\nRun `gh pr %s` as its own " \
                     "command." % sub
        else:
            reason = evaluate(source, top, sub, args, command, m.group(0))
            if not reason and sub == "create":
                # From the flags to the end: a quoted body may span lines.
                reason = ticket_reason(top, payload.get("cwd") or os.getcwd(), command[m.start(2):])
        if reason:
            print("Blocked `gh pr %s`: %s" % (sub, reason), file=sys.stderr)
            return 2
    return 0


if __name__ == "__main__":
    sys.exit(main())
