#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Check that every relative link in a tracked Markdown file resolves to a repository path.

A link to a path the repository does not have is a false claim to every reader, agents
included. Checked: inline links and images, reference definitions, HTML href/src. Skipped:
absolute URLs, protocol-relative //host URLs, site-absolute /path links, pure
#anchors, and anything inside a code span or fenced code block. A
target resolves when it is a tracked or untracked-but-not-ignored file, or a directory
holding one; build outputs do not count. KNOWN_BROKEN lists the links that were already
broken when this check was added; an entry that no longer matches a broken link is
reported too, so the list only shrinks. Every run first checks a planted-violation
fixture and exits 2 if the checker no longer reports exactly the planted links. A file
whose code fences do not balance is reported as a violation, because lines past an
unclosed fence cannot be checked.

Exit codes: 0 clean, 1 violations, 2 environment error or self-test failure.
"""

import argparse
import os
import posixpath
import re
import subprocess
import sys
from urllib.parse import unquote

# (document, link target as written): remove an entry when its link is fixed.
KNOWN_BROKEN = {
    ("test-validation/README.md", "../test-apps/README.md"),
    ("test-validation/README.md", "./.gitlab/dd-trace-integration/.gitlab-ci.yml"),
}

_REF_DEF = re.compile(r"^ {0,3}\[[^\]]+\]:\s+(?:<([^>]*)>|(\S+))")
_HTML = re.compile(r"""(?:href|src)\s*=\s*["']([^"']+)["']""")
_FENCE = re.compile(r"^ {0,3}(```+|~~~+)")
_SCHEME = re.compile(r"^[a-zA-Z][a-zA-Z0-9+.\-]*:")


def targets(text):
    """(line number, link text, raw target) for every link outside code; split on \\n
    only so line numbers match grep and editors. The text is quoted in diagnostics so
    a rejection names the offending line, not just the target. Link text may nest one
    level of brackets and the destination may hold balanced parentheses (CommonMark);
    a destination spanning lines is not recognized, because targets() is line-based so
    diagnostics name the offending line. A fence closes only on
    a bare marker line of the same character and at least the opening length
    (CommonMark forbids an info string on a closing fence); lines past an unclosed
    fence are skipped and reported by unbalanced()."""
    fence = None  # (char, opening length, opening line number)
    for lineno, line in enumerate(text.split("\n"), 1):
        m = _FENCE.match(line)
        if m:
            ch, size = m.group(1)[0], len(m.group(1))
            if fence is None:
                fence = (ch, size, lineno)
            elif ch == fence[0] and size >= fence[1] and not line[m.end():].strip():
                fence = None
            continue
        if fence is not None:
            continue
        line = re.sub(r"(?<!`)(`+)(?!`)(.*?)(?<!`)\1(?!`)", "", line)
        for label, raw in _inline_links(line):
            yield lineno, label, raw
        m = _REF_DEF.match(line)
        if m:
            raw = m.group(1) or m.group(2)
            yield lineno, "[%s]" % m.group(0)[1:m.group(0).find("]")], raw
        for m in _HTML.finditer(line):
            yield lineno, m.group(0), m.group(1)


def _inline_links(line):
    """(link text, raw destination) for [text](dest) and ![alt](dest), with balanced
    brackets in the text and a destination parsed with full parenthesis nesting
    ([x](doc((1)).md) names doc((1)).md, not doc). Escaped brackets are literal."""
    i, n = 0, len(line)
    while i < n:
        if line[i] == "\\":
            i += 2
            continue
        if line[i] != "[":
            i += 1
            continue
        depth, j = 1, i + 1
        while j < n and depth:
            if line[j] == "\\":
                j += 1
            elif line[j] == "[":
                depth += 1
            elif line[j] == "]":
                depth -= 1
            j += 1
        if depth or j >= n or line[j] != "(":
            # a closed non-link bracket resumes after its "]"; an unclosed one
            # re-parses its contents as ordinary text (CommonMark)
            i = j if not depth else i + 1
            continue
        k = j + 1
        while k < n and line[k] in " \t":
            k += 1
        if k < n and line[k] == "<":
            end = line.find(">", k + 1)
            if end == -1:
                i = i + 1
                continue
            yield line[i + 1:j - 1], line[k + 1:end]
            i = end + 1
            continue
        paren, k2 = 1, k
        while k2 < n:
            c = line[k2]
            if c == "\\":
                k2 += 1
            elif c == "(":
                paren += 1
            elif c == ")":
                paren -= 1
                if paren == 0:
                    break
            elif c.isspace() and paren == 1:
                break  # whitespace ends the destination; a title may follow
            k2 += 1
        if paren != 0:
            # whitespace ended the destination at depth 1: a title follows up to the
            # ")" that closes the link's own opening parenthesis
            depth2, k3 = 1, k2
            while k3 < n:
                c = line[k3]
                if c == "\\":
                    k3 += 1
                elif c == "(":
                    depth2 += 1
                elif c == ")":
                    depth2 -= 1
                    if depth2 == 0:
                        break
                k3 += 1
            if depth2 != 0:
                i = i + 1  # CommonMark re-parses an unclosed link's contents as text
                continue
            yield line[i + 1:j - 1], line[k:k2]
            i = k3 + 1
            continue
        yield line[i + 1:j - 1], line[k:k2]
        i = k2 + 1


def unbalanced(text):
    """Line number of a code fence that is never closed, or None. A file with one is
    only checked down to that line, so it must be reported, never silently skipped."""
    fence = None
    for lineno, line in enumerate(text.split("\n"), 1):
        m = _FENCE.match(line)
        if m:
            ch, size = m.group(1)[0], len(m.group(1))
            if fence is None:
                fence = (ch, size, lineno)
            elif ch == fence[0] and size >= fence[1] and not line[m.end():].strip():
                fence = None
    return fence[2] if fence else None


def resolve(doc, raw):
    """Repo-relative path the link names, or None when it is not a repository-relative
    link. A protocol-relative //host/path URL names a site, and a site-absolute /path
    link resolves against the site root on GitHub, not the repository — both are
    skipped rather than guessed at. Fragments and queries split before percent-decoding:
    README.md%23x.md names the file README.md#x.md, not a fragment of README.md."""
    raw = raw.strip()
    target = unquote(raw.split("#", 1)[0].split("?", 1)[0])
    if not target or _SCHEME.match(raw) or target.startswith("/"):
        return None
    return posixpath.normpath(posixpath.join(posixpath.dirname(doc), target))


def broken_links(docs, paths):
    """(doc, line, link text, raw target) for each link in docs ({path: text}) that
    names neither a path in `paths` nor a directory holding one."""
    dirs = set()
    for p in paths:
        while p:
            parent = posixpath.dirname(p)
            p = posixpath.normpath(parent) if parent else "."
            dirs.add(p)
            if p == ".":
                break
    out = []
    for doc in sorted(docs):
        for lineno, label, raw in targets(docs[doc]):
            rel = resolve(doc, raw)
            if rel is not None and rel not in paths and rel not in dirs:
                out.append((doc, lineno, label, raw))
    return out


def _listed_paths(root, cands):
    """Repo paths under the literal candidate pathspecs: tracked, or untracked and not
    ignored — the same universe the full `git ls-files --cached --others
    --exclude-standard` enumeration returns, restricted to the candidate paths. Raises
    on a git failure."""
    argv = ["git", "-C", root, "ls-files", "-z", "--cached", "--others",
            "--exclude-standard", "--"] + [":(literal)" + c for c in cands]
    res = subprocess.run(argv, stdout=subprocess.PIPE, check=True)
    return {p.decode("utf-8", "surrogateescape") for p in res.stdout.split(b"\0") if p}


def report(broken, known, include_stale=True):
    """Violation lines: broken links not in `known`, and (unless include_stale is false)
    `known` entries no longer broken. Each line quotes the link text so the rejection
    names the offending line."""
    seen = {(doc, raw) for doc, _, _, raw in broken}
    lines = ["%s:%d: broken link %r (link text %r) (no such path in the repository)"
             % (doc, n, raw, label)
             for doc, n, label, raw in broken if (doc, raw) not in known]
    if include_stale:
        lines += ["%s: KNOWN_BROKEN entry %r is no longer broken; remove it" % entry
                  for entry in sorted(known - seen)]
    return lines


def self_test():
    docs = {
        "doc/A.md": "\n".join([
            "[ok](B.md) [dir](sub) [root](..) [anchor](#x) [web](https://example.com/y.md) [cdn](//cdn.example.com/i.png) [abs](/doc/README.md)",
            "[bad](Missing.md)",                        # EXPECT line 2
            "[outer [inner] text](Missing2.md)",        # EXPECT line 3: nested text brackets
            "`[code](Nope.md)`",
            "```",
            "[fenced](Nope.md)",
            "```",
            '<img src="../img/gone.png"> [frag](B.md#sec) [diff](D(2).md) ![lost](../img/lost.png)',  # EXPECT src, lost
            "[ref]: ../top.md",
            "[known](Old.md) [deep](../deep/x) [gone2](absent(2).md)",  # EXPECT absent(2).md
            "``[spanskip](Nope2.md)`` [spanbad](Missing3.md) [deep2](doc((1)).md)",  # EXPECT Missing3, doc((1)).md
            "[enc](missing%23x.md)",                    # EXPECT missing%23x.md (decoded to missing#x.md)
            '[titled](Missing4.md "the title") [t2](B.md "t") [esc]\\[skip](Nope4.md)\\]',  # EXPECT Missing4
            '[unterm](Missing5.md "open [real](Missing6.md)',  # EXPECT Missing6: the unclosed construct is text
            '[unclosed [real2](Missing7.md)',  # EXPECT Missing7: an unclosed bracket is text
        ]),
        "doc/B.md": "",
    }
    paths = {"doc/A.md", "doc/B.md", "doc/sub/C.md", "top.md", "deep/x/y/Z.md", "doc/D(2).md"}
    known = {("doc/A.md", "Old.md"), ("doc/A.md", "Fixed.md")}
    got = report(broken_links(docs, paths), known)
    want = ["doc/A.md:2: broken link 'Missing.md' (link text 'bad') (no such path in the repository)",
            "doc/A.md:3: broken link 'Missing2.md' (link text 'outer [inner] text') (no such path in the repository)",
            "doc/A.md:8: broken link '../img/lost.png' (link text 'lost') (no such path in the repository)",
            "doc/A.md:8: broken link '../img/gone.png' (link text 'src=\"../img/gone.png\"') (no such path in the repository)",
            "doc/A.md:10: broken link 'absent(2).md' (link text 'gone2') (no such path in the repository)",
            "doc/A.md:11: broken link 'Missing3.md' (link text 'spanbad') (no such path in the repository)",
            "doc/A.md:11: broken link 'doc((1)).md' (link text 'deep2') (no such path in the repository)",
            "doc/A.md:12: broken link 'missing%23x.md' (link text 'enc') (no such path in the repository)",
            "doc/A.md:13: broken link 'Missing4.md' (link text 'titled') (no such path in the repository)",
            "doc/A.md:14: broken link 'Missing6.md' (link text 'real') (no such path in the repository)",
            "doc/A.md:15: broken link 'Missing7.md' (link text 'real2') (no such path in the repository)",
            "doc/A.md: KNOWN_BROKEN entry 'Fixed.md' is no longer broken; remove it"]
    if got != want:
        return False, got
    # A fence line with an info string opens a fence; it never closes one (CommonMark).
    # An unclosed fence must silence the rest of the file and must be detectable.
    tricky = """```bash
[skipped](Nope.md) inside the bash fence
   ```bash
[skipped](Nope.md) inside the nested fence
```
[reported](Nope.md)
"""
    if [t[1:] for t in targets(tricky)] != [("reported", "Nope.md")]:
        return False, ["info-string fence must not close"]
    if unbalanced(tricky) is not None:
        return False, ["balanced tricky text reported unbalanced"]
    dangling = "```bash\n[skipped](Nope.md)\n"
    if unbalanced(dangling) != 1 or list(targets(dangling)):
        return False, ["unclosed fence must silence and be reported"]
    return True, want


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                    help="repository root (default: the checkout containing this script)")
    ap.add_argument("--check-file", metavar="DOC",
                    help="check markdown content from stdin as repo-relative doc DOC against "
                         "the repository's current paths; exit 1 on violations (used by the "
                         "doc-links write guards)")
    args = ap.parse_args(argv)
    root = args.root

    ok, got = self_test()
    if not ok:
        print("doc links: self-test FAILED, checker drift; got:\n  " + "\n  ".join(got))
        return 2
    if args.check_file is not None:
        # A single incoming write: skip stale-KNOWN_BROKEN reporting, or fixing one of
        # those links in a rewritten file would be blocked as a violation.
        content = sys.stdin.read()
        docs = {args.check_file: content}
        # Only the targets this document names need resolving: query git for exactly
        # those pathspecs instead of enumerating the whole repository, because the
        # write guards run this on every markdown write. A target outside the checkout
        # (leading "..") can never be in paths, so it is skipped and reported broken.
        cands = {resolve(args.check_file, raw) for _, _, raw in targets(content)}
        cands.discard(None)
        inside = {c for c in cands if c not in {".", ".."} and not c.startswith("../")}
        paths = {args.check_file}  # the incoming document exists prospectively
        if "." in cands:
            paths.add(".")  # the repository root itself always resolves
        try:
            if inside:
                paths |= _listed_paths(root, inside)
        except (OSError, subprocess.CalledProcessError) as exc:
            print("doc links: git ls-files failed: %s" % exc, file=sys.stderr)
            return 2
        lines = report(broken_links(docs, paths), KNOWN_BROKEN, include_stale=False)
        ln = unbalanced(content)
        if ln is not None:
            lines.append("%s:%d: unclosed code fence; lines after it are not checked"
                         % (args.check_file, ln))
        for line in lines:
            print(line)
        return 1 if lines else 0
    try:
        res = subprocess.run(["git", "-C", root, "ls-files", "-z", "--cached", "--others",
                              "--exclude-standard"], stdout=subprocess.PIPE, check=True)
    except (OSError, subprocess.CalledProcessError) as exc:
        print("doc links: git ls-files failed: %s" % exc, file=sys.stderr)
        return 2
    paths = {p.decode("utf-8", "surrogateescape") for p in res.stdout.split(b"\0") if p}
    docs = {}
    for doc in paths:
        full = os.path.join(root, doc)
        if doc.endswith((".md", ".markdown")) and os.path.isfile(full):
            with open(full, encoding="utf-8", errors="replace") as fh:
                docs[doc] = fh.read()
    lines = report(broken_links(docs, paths), KNOWN_BROKEN)
    for doc in sorted(docs):
        ln = unbalanced(docs[doc])
        if ln is not None:
            lines.append("%s:%d: unclosed code fence; lines after it are not checked" % (doc, ln))
    for line in lines:
        print(line)
    if lines:
        return 1
    print("doc links: OK")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
