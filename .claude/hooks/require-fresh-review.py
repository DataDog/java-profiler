#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Claude Code PreToolUse hook: block commands that mention `gh pr create|new|ready`
while the branch's review marker is stale, and `gh pr create` whose title and body
reference no ticket. Pushes are gated by .githooks/pre-push."""

import json
import os
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
    """Check arguments for the PR `gh pr ready` targets, from GitHub so the commits the
    PR holds are checked; [] means the current branch, None that it cannot be resolved."""
    selector = [a for i, a in enumerate(args)
                if not a.startswith("-") and (i == 0 or args[i - 1] not in ("-R", "--repo"))]
    out = gh_query(["pr", "view", *selector[:1], *(["-R", repo] if repo else []), "--json",
                    "headRefName,headRefOid,baseRefName", "-q",
                    '.headRefName + " " + .headRefOid + " " + .baseRefName'], cwd)
    if not out or len(out.split()) != 3:
        return None if selector else []
    head, oid, base = out.split()
    return ["--branch", head, "--commit", oid, "--base", origin(base)]


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


def pr_text(rest, cwd):
    """The title and body `gh pr create` will use, or None when unsure (CI checks those).
    Only a simple command with literal values is judged; as in gh, the last flag wins,
    --body-file beats --body, and explicit values beat a fill flag."""
    try:
        lexer = shlex.shlex(rest, posix=True, punctuation_chars="();<>|&\n")
        lexer.whitespace = " \t\r"
        lexer.commenters = ""
        lexer.whitespace_split = True
        tokens = list(lexer)
    except ValueError:
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
        extra = ready_target(args, repo_flag(words(match_text)), cwd)
        if extra is None:
            return "cannot resolve the PR's head commit (gh failed); retry when gh works."
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
    command = payload.get("tool_input", {}).get("command", "").replace("\\\n", " ")
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
