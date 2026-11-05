#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.

# Tests for utils/review-marker.py, .githooks/pre-push and the Claude Code hook
# .claude/hooks/require-fresh-review.py, each group in a throwaway repo with a bare
# origin and a `gh` stub; global git config is ignored so signing cannot interfere.

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
ROOT=$(cd "$SCRIPT_DIR/../.." && pwd)
PY=$(command -v python3)
REAL_GIT=$(command -v git)
TESTS=0
FAILED=0
export PYTHONDONTWRITEBYTECODE=1 GIT_CONFIG_GLOBAL=/dev/null GIT_CONFIG_NOSYSTEM=1

TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT

pass() { TESTS=$((TESTS + 1)); }
fail() { TESTS=$((TESTS + 1)); FAILED=$((FAILED + 1)); echo "FAIL: $*" >&2; }

# gh stub, logging each call to $GH_LOG: `pr list --head B` reports an open PR when
# B is in $OPEN_PRS; `pr view <sel>` prints "$VIEW_HEAD $VIEW_OID $VIEW_BASE" unless
# <sel> looks like a repo (or $VIEW_REPO is set and not passed as -R); `repo view`
# prints $DEFAULT_BRANCH; $GH_FAIL fails all.
mkdir -p "$TEMP_DIR/bin" "$TEMP_DIR/oldgit" "$TEMP_DIR/nogh"
cat > "$TEMP_DIR/bin/gh" <<'EOF'
#!/bin/sh
echo "$*" >> "$GH_LOG"
[ -z "$GH_FAIL" ] || exit 1
case "$1 $2" in
  "pr list") for b in $OPEN_PRS; do [ "$b" = "$4" ] && { echo 1; exit 0; }; done
             echo 0; exit 0 ;;
  "pr view") case "$3" in */*) exit 1 ;; esac
             [ -z "$VIEW_REPO" ] || case " $* " in *" -R $VIEW_REPO "*) ;; *) exit 1 ;; esac
             [ -n "$VIEW_HEAD" ] && echo "$VIEW_HEAD $VIEW_OID $VIEW_BASE" && exit 0; exit 1 ;;
  "repo view") [ -n "$DEFAULT_BRANCH" ] && echo "$DEFAULT_BRANCH" && exit 0; exit 1 ;;
esac
exit 1
EOF
chmod +x "$TEMP_DIR/bin/gh"
# git that reports an old version, for the version gate.
printf '#!/bin/sh\n[ "$1" = version ] && { echo "git version 2.34.1"; exit 0; }\nexec "%s" "$@"\n' \
  "$REAL_GIT" > "$TEMP_DIR/oldgit/git" && chmod +x "$TEMP_DIR/oldgit/git"
for v in 2.38.9 2.39.0; do
  mkdir -p "$TEMP_DIR/git-$v"
  printf '#!/bin/sh\n[ "$1" = version ] && { echo "git version %s"; exit 0; }\nexec "%s" "$@"\n' \
    "$v" "$REAL_GIT" > "$TEMP_DIR/git-$v/git" && chmod +x "$TEMP_DIR/git-$v/git"
done
# gh that cannot be executed, for the pre-push OSError fail-open path.
printf '#!/bin/sh\n' > "$TEMP_DIR/nogh/gh" && chmod -x "$TEMP_DIR/nogh/gh"
export PATH="$TEMP_DIR/bin:$PATH" GH_LOG="$TEMP_DIR/gh.log"
export OPEN_PRS="" VIEW_HEAD="" VIEW_OID="" VIEW_BASE="" VIEW_REPO="" GH_FAIL="" DEFAULT_BRANCH=""

# Repo whose origin/main carries the gate scripts (in a second commit, $PRE_GATE being
# the first) and a feature branch holding one commit.
new_repo() {
  local dir="$TEMP_DIR/$1"
  git init -q --bare "$dir-origin.git"
  mkdir -p "$dir" && cd "$dir"
  git init -q -b main
  git config user.email t@example.com && git config user.name t
  for i in 1 2 3 4 5 6 7 8; do echo "line $i"; done > a.txt
  echo other > b.txt
  git add . && git commit -qm base
  PRE_GATE=$(git rev-parse HEAD)
  mkdir -p utils .githooks .claude/hooks
  cp "$ROOT/utils/review-marker.py" utils/
  cp "$ROOT/.githooks/pre-push" .githooks/
  cp "$ROOT/.claude/hooks/require-fresh-review.py" .claude/hooks/
  mkdir -p .pi/extensions && cp "$ROOT/.pi/extensions/require-fresh-review.ts" .pi/extensions/
  git add utils .githooks .claude .pi && git commit -qm gate
  git remote add origin "$dir-origin.git" && git push -q origin main
  git checkout -qb feature
  sed -i.bak 's/line 2/line 2 changed/' a.txt && rm a.txt.bak && git commit -qam change
}

# A stand-in for tampered checkout code: it leaves $TEMP_DIR/pwned behind if it ever runs.
PAYLOAD=$(printf 'import sys\nopen("%s/pwned", "w").close()\nsys.exit(0)\n' "$TEMP_DIR")
not_run() {
  if [ -e "$TEMP_DIR/pwned" ]; then fail "$1: checkout code ran"; rm "$TEMP_DIR/pwned"; else pass; fi
}
# Stdlib-named payloads at the checkout root, where git runs hooks.
plant() { for m in argparse subprocess; do printf '%s' "$PAYLOAD" > "$m.py"; done; }
unplant() { rm -f argparse.py subprocess.py; }

marker() { python3 utils/review-marker.py "$@"; }

# expect <name> <expected-exit> <output-substring-or-empty> <command...>
expect() {
  local name=$1 want=$2 needle=$3; shift 3
  local rc=0
  "$@" >"$TEMP_DIR/out" 2>"$TEMP_DIR/err" || rc=$?
  if [ "$rc" -ne "$want" ]; then
    fail "$name: exit $rc, want $want ($(cat "$TEMP_DIR/err"))"
  elif [ -n "$needle" ] && ! cat "$TEMP_DIR/out" "$TEMP_DIR/err" | grep -qF -- "$needle"; then
    fail "$name: output lacks '$needle': $(cat "$TEMP_DIR/out" "$TEMP_DIR/err")"
  else
    pass
  fi
}

# --- review-marker.py ---
new_repo m
expect "check without marker" 1 "no review marker for branch feature" marker check
echo dirty >> b.txt
expect "write refuses uncommitted changes" 2 "uncommitted changes" marker write --tool t
git checkout -q b.txt
expect "write" 0 "" marker write --tool t --session s1
expect "check fresh" 0 "" marker check
expect "write through the trusted runner" 0 "review marker written" \
  sh -c 'git show refs/remotes/origin/main:utils/review-marker.py | python3 -I - write --tool t'
expect "check fresh after the trusted runner" 0 "" marker check
echo scratch > scratch.txt
expect "untracked scratch is ignored" 0 "" marker check
REVIEWED=$(git rev-parse HEAD)

git checkout -q main && echo advance > c.txt && git add c.txt && git commit -qm advance \
  && git push -q origin main && git checkout -q feature
expect "advancing base keeps marker fresh" 0 "" marker check
git rebase -q origin/main
expect "clean rebase keeps marker fresh" 0 "" marker check
git checkout -q main && sed -i.bak 's/line 4/line 4 upstream/' a.txt && rm a.txt.bak \
  && git commit -qam near && git push -q origin main && git checkout -q feature && git rebase -q origin/main
expect "rebase past an adjacent upstream change errs toward stale" 1 "is stale" marker check
marker write --tool t >/dev/null
REVIEWED=$(git rev-parse HEAD)

echo extra >> b.txt && git commit -qam extra
expect "new commit is stale" 1 "is stale" marker check
expect "check --commit of the reviewed tip" 0 "" marker check --commit "$REVIEWED"
expect "check --commit unknown locally" 2 "is not available locally" \
  marker check --commit 1234567890123456789012345678901234567890
git reset -q --hard HEAD~1
expect "dropping the commit is fresh again" 0 "" marker check
git commit -q --amend -m change2 && echo amend >> a.txt && git commit -q --amend -am change3
expect "amended content is stale" 1 "is stale" marker check
git reset -q --hard HEAD@{2}
expect "reflog back to reviewed content" 0 "" marker check

echo unreviewed >> b.txt && git commit -qam unreviewed && git checkout -q HEAD~1 -- b.txt
expect "committed change reverted only in worktree is stale" 1 "is stale" marker check
git checkout -q HEAD -- b.txt && git reset -q --hard HEAD~1

sed -i.bak 's/^line 2 changed/  line 2 changed/' a.txt && rm a.txt.bak && git commit -qam indent
expect "whitespace-only change is stale" 1 "is stale" marker check
git reset -q --hard HEAD~1
echo added >> b.txt && git commit -qam add-line && marker write --tool t >/dev/null
git reset -q --hard HEAD~1 && { echo added; cat b.txt; } > b.new && mv b.new b.txt && git commit -qam moved
expect "moving an added line is stale" 1 "is stale" marker check
git reset -q --hard HEAD~1 && marker write --tool t >/dev/null

expect "check against another base" 1 "covered base origin/main, not origin/other" \
  marker check --base origin/other

git worktree add -q -b other ../m-wt origin/main
(cd ../m-wt && echo wt >> b.txt && git commit -qam wt && python3 "$PWD/../m/utils/review-marker.py" write --tool t >/dev/null)
expect "marker written in another worktree is visible" 0 "" marker check --branch other

git checkout -qb topic/slash && expect "write slashed branch" 0 "" marker write --tool t
git checkout -qb topic%2Fslash && echo pct >> b.txt && git commit -qam pct && marker write --tool t >/dev/null
expect "check slashed branch beside a %2F twin" 0 "" marker check --branch topic/slash
expect "check the %2F twin" 0 "" marker check --branch topic%2Fslash
git checkout -q feature && git branch -qD topic/slash
expect "marker of a deleted branch" 2 "is not available locally" marker check --branch topic/slash

git checkout -q --detach
expect "write on detached HEAD" 2 "HEAD is detached" marker write --tool t
git checkout -q feature
expect "write with unknown base" 2 "git merge-base" marker write --tool t --base origin/nope
PATH="$TEMP_DIR/oldgit:$PATH" expect "git older than 2.39 is reported" 2 "git 2.39 or newer is required" \
  marker check
marker write --tool t >/dev/null
PATH="$TEMP_DIR/git-2.38.9:$PATH" expect "git 2.38.9 is rejected" 2 "git 2.39 or newer is required" marker check
PATH="$TEMP_DIR/git-2.39.0:$PATH" expect "git 2.39.0 is accepted" 0 "" marker check
MF=.git/review-markers/$(printf feature | shasum -a 256 | cut -c1-32).json
cp "$MF" "$TEMP_DIR/feature.json"
echo '{' > "$MF"
expect "corrupt marker" 1 "not valid JSON" marker check
sed 's/"branch": "feature"/"branch": "other-name"/' "$TEMP_DIR/feature.json" > "$MF"
expect "marker recorded for another branch name" 1 "no review marker for branch feature" marker check
cp "$TEMP_DIR/feature.json" "$MF"
git tag origin/main "$PRE_GATE"
expect "digest ignores a tag named origin/main" 0 "" marker check
git tag -d origin/main >/dev/null
git tag feature HEAD
expect "write beside a same-named tag" 0 "written for feature " marker write --tool t
expect "check beside a same-named tag" 0 "" marker check --branch feature
git tag -d feature >/dev/null
mkdir -p "$TEMP_DIR/nogit" && cd "$TEMP_DIR/nogit"
expect "outside a git repo" 2 "review-marker:" python3 "$ROOT/utils/review-marker.py" check

# --- install-hook ---
new_repo i
expect "install-hook installs the shim" 0 "pre-push hook installed" marker install-hook
if [ -x .git/hooks/pre-push ]; then pass; else fail "install-hook: shim not executable"; fi
expect "install-hook is idempotent" 0 "already installed" marker install-hook
printf '#!/bin/sh\n# Installed by utils/review-marker.py install-hook (old)\n' > .git/hooks/pre-push
expect "install-hook upgrades an older shim" 0 "pre-push hook installed" marker install-hook
expect "install-hook is idempotent after upgrade" 0 "already installed" marker install-hook
echo '#!/bin/sh' > .git/hooks/pre-push
expect "install-hook keeps a foreign hook" 2 "is not this repo's shim" marker install-hook
rm .git/hooks/pre-push && git config core.hooksPath /elsewhere
expect "install-hook notes a set core.hooksPath" 0 "core.hooksPath is /elsewhere" marker install-hook
git config --unset core.hooksPath

# --- .githooks/pre-push (stdin: <local ref> <local sha> <remote ref> <remote sha>) ---
new_repo p
prepush() { printf '%s\n' "$1" | python3 .githooks/pre-push origin "$TEMP_DIR/p-origin.git"; }
TIP=$(git rev-parse HEAD)
Z=0000000000000000000000000000000000000000
export OPEN_PRS="feature"
expect "pre-push blocks open-PR branch without marker" 1 "Run the pre-pr-review skill" \
  prepush "refs/heads/feature $TIP refs/heads/feature $Z"
expect "pre-push allows deletion" 0 "" prepush "(delete) $Z refs/heads/feature $TIP"
expect "pre-push allows a SHA-256 deletion" 0 "" \
  prepush "(delete) ${Z}${Z:0:24} refs/heads/feature $TIP"
: > "$GH_LOG"
expect "pre-push allows tags" 0 "" prepush "refs/tags/v1 $TIP refs/tags/v1 $Z"
if grep -q "pr list" "$GH_LOG"; then fail "pre-push gated a tag push (asked gh about it)"; else pass; fi
OPEN_PRS="" expect "pre-push allows branch without open PR" 0 "" \
  prepush "refs/heads/feature $TIP refs/heads/feature $Z"
GH_FAIL=1 expect "pre-push fails open when gh fails" 0 "" \
  prepush "refs/heads/feature $TIP refs/heads/feature $Z"
PATH="$TEMP_DIR/nogh:/usr/bin:/bin" expect "pre-push fails open when gh cannot run" 0 "" \
  sh -c "printf '%s\n' 'refs/heads/feature $TIP refs/heads/feature $Z' | $PY .githooks/pre-push"
marker write --tool t >/dev/null
: > "$GH_LOG"
expect "pre-push allows reviewed commits" 0 "" prepush "refs/heads/feature $TIP refs/heads/feature $Z"
if [ -s "$GH_LOG" ]; then fail "pre-push with a fresh marker called gh: $(cat "$GH_LOG")"; else pass; fi
echo more >> b.txt && git commit -qam more
STALE=$(git rev-parse HEAD)
expect "pre-push blocks unreviewed tip" 1 "is stale" \
  prepush "refs/heads/feature $STALE refs/heads/feature $Z"
printf '%s' "$PAYLOAD" > utils/review-marker.py
expect "pre-push uses origin/main's marker script" 1 "is stale" \
  prepush "refs/heads/feature $STALE refs/heads/feature $Z"
not_run "pre-push with a tampered utils/review-marker.py"
git checkout -q utils/review-marker.py
GATE=$(git rev-parse origin/main) && git update-ref refs/remotes/origin/main "$PRE_GATE"
expect "pre-push allows while origin/main has no gate" 0 "" \
  prepush "refs/heads/feature $STALE refs/heads/feature $Z"
git update-ref refs/remotes/origin/main "$GATE"
plant
expect "pre-push ignores stdlib-named files in the checkout" 1 "is stale" \
  prepush "refs/heads/feature $STALE refs/heads/feature $Z"
not_run "pre-push with planted argparse.py/subprocess.py"
unplant
git tag origin/main "$PRE_GATE"
expect "pre-push ignores a tag named origin/main" 1 "is stale" \
  prepush "refs/heads/feature $STALE refs/heads/feature $Z"
git tag -d origin/main >/dev/null
expect "pre-push gates \`git push origin HEAD\`" 1 "is stale" \
  prepush "HEAD $STALE refs/heads/feature $Z"
git tag feature HEAD
expect "pre-push HEAD refspec beside a same-named tag" 1 "is stale" \
  prepush "HEAD $STALE refs/heads/feature $Z"
git tag -d feature >/dev/null
expect "pre-push gates \`git push origin <sha>:feature\`" 1 "is stale" \
  prepush "$STALE $STALE refs/heads/feature $Z"
git checkout -q --detach "$TIP"
expect "pre-push on detached HEAD uses the remote branch's marker" 0 "" \
  prepush "HEAD $TIP refs/heads/feature $Z"
git checkout -q feature

# The current branch (side) has no marker; only feature's marker can make this pass.
git checkout -qb side
expect "pre-push checks the pushed branch, not the current one" 0 "" \
  prepush "refs/heads/feature $TIP refs/heads/feature $Z"
git checkout -q feature

git update-ref refs/remotes/origin/tmp origin/main
git reset -q --hard "$TIP" && marker write --tool t --base origin/tmp >/dev/null
git update-ref -d refs/remotes/origin/tmp
expect "pre-push env error says how to proceed" 1 "push with --no-verify" \
  prepush "refs/heads/feature $TIP refs/heads/feature $Z"
marker write --tool t >/dev/null

marker install-hook >/dev/null
echo more >> b.txt && git commit -qam more
expect "real git push through the shim refuses unreviewed commits" 1 "is stale" git push -q origin feature
printf '%s' "$PAYLOAD" > .githooks/pre-push
expect "shim runs origin/main's hook, not the checkout's" 1 "is stale" git push -q origin feature
not_run "shim with a tampered .githooks/pre-push"
git checkout -q .githooks/pre-push
GATE=$(git rev-parse origin/main) && git update-ref refs/remotes/origin/main "$PRE_GATE"
expect "shim allows the push while origin/main has no gate" 0 "" git push -q origin feature
git update-ref refs/remotes/origin/main "$GATE"
echo again >> b.txt && git commit -qam again
plant
expect "shim ignores stdlib-named files in the checkout" 1 "is stale" git push -q origin feature
not_run "shim with planted argparse.py/subprocess.py"
unplant
git tag origin/main "$PRE_GATE"
expect "shim ignores a tag named origin/main" 1 "is stale" git push -q origin feature
git tag -d origin/main >/dev/null
git reset -q --hard "$TIP"
expect "real git push of reviewed commits succeeds" 0 "" git push -q -f origin feature
export OPEN_PRS=""

# --- .claude/settings.json hook command ---
HOOK_CMD=$(python3 -c 'import json,sys; print(json.load(open(sys.argv[1]))["hooks"]["PreToolUse"][0]["hooks"][0]["command"])' \
  "$ROOT/.claude/settings.json")
mkdir -p "$TEMP_DIR/nohook"
expect "settings hook command allows everything when the hook file is missing" 0 "" \
  sh -c "echo '{\"tool_input\":{\"command\":\"gh pr create\"}}' | CLAUDE_PROJECT_DIR=$TEMP_DIR/nohook sh -c '$HOOK_CMD'"

# --- .claude/hooks/require-fresh-review.py ---
new_repo h
git worktree add -q -b wt ../h-wt origin/main
(cd ../h-wt && echo wt >> b.txt && git commit -qam wt && python3 "$PWD/../h/utils/review-marker.py" write --tool t >/dev/null)
WT_TIP=$(git rev-parse wt)
(cd ../h-wt && echo more >> b.txt && git commit -qam more)
WT_STALE=$(git rev-parse wt)
(cd ../h-wt && git reset -q --hard "$WT_TIP")
mkdir -p "$TEMP_DIR/elsewhere" && (cd "$TEMP_DIR/elsewhere" && git init -q)
hook() {
  python3 -c 'import json,sys; print(json.dumps({"cwd": sys.argv[2], "tool_input": {"command": sys.argv[1]}}))' \
    "$1" "${2:-$PWD}" | CLAUDE_PROJECT_DIR=$PWD python3 .claude/hooks/require-fresh-review.py
}
STALE_MSG="Run the pre-pr-review skill"
expect "hook ignores unrelated command" 0 "" hook "ls -la"
expect "hook ignores bad payload" 0 "" sh -c 'echo nope | python3 .claude/hooks/require-fresh-review.py'
expect "hook blocks pr create without marker" 2 "$STALE_MSG" hook "gh pr create --fill"
expect "hook blocks a quoted mention while stale (accepted false positive)" 2 "$STALE_MSG" \
  hook 'grep -n "gh pr create" AGENTS.md'
: > "$GH_LOG"
expect "hook gates a later line" 2 "$STALE_MSG" hook "$(printf 'git push -u origin feature\ngh pr create --fill')"
if grep -q "repo view" "$GH_LOG"; then fail "hook looked up the default base before a failing check"; else pass; fi
expect "hook gates a subshell" 2 "$STALE_MSG" hook "(gh pr create --fill)"
expect "hook gates if/then" 2 "$STALE_MSG" hook "if true; then gh pr create; fi"
expect "hook gates a brace group" 2 "$STALE_MSG" hook "{ gh pr create; }"
expect "hook gates bash -c" 2 "$STALE_MSG" hook "bash -c 'gh pr create'"
expect "hook gates time" 2 "$STALE_MSG" hook "time gh pr create"
expect "hook gates gh pr new" 2 "$STALE_MSG" hook "gh pr new --fill"
expect "hook gates prefixed gh" 2 "$STALE_MSG" hook "GH_REPO=o/r command /opt/homebrew/bin/gh -R o/r pr create"
expect "hook gates despite apostrophe in a heredoc body" 2 "$STALE_MSG" \
  hook "$(printf "gh pr create --body-file - <<'EOF'\nIt's fixed\nEOF")"
expect "hook blocks a command that changes directory" 2 "another checkout" \
  hook "cd ../h-wt && gh pr create --fill"
expect "hook does not mistake %cd for cd" 2 "$STALE_MSG" hook "git log --format=%cd; gh pr create"
expect "hook allows ready --undo even with cd" 0 "" hook "cd .. && gh pr ready --undo"
expect "hook allows other repositories" 0 "" hook "gh pr create --fill" "$TEMP_DIR/elsewhere"
expect "hook allows non-git directories" 0 "" hook "gh pr create --fill" "$TEMP_DIR/nogit"
expect "hook uses payload cwd" 0 "" hook "gh pr create --fill" "$TEMP_DIR/h-wt"
expect "hook blocks --head" 2 "--head names a branch" hook "gh pr create --head wt"
expect "hook blocks -H" 2 "--head names a branch" hook "gh pr create -H wt"
expect "hook blocks --head on a continuation line" 2 "--head names a branch" \
  hook "$(printf 'gh pr create --fill \\\n  --head wt')"
expect "hook checks every gh pr command on a line" 2 "$STALE_MSG" hook "gh pr ready --undo && gh pr create --fill"
expect "hook blocks pushd" 2 "another checkout" hook "pushd ../h-wt && gh pr create"
expect "hook blocks GIT_DIR" 2 "another checkout" hook "GIT_DIR=../x/.git gh pr create"
expect "hook blocks env -C" 2 "another checkout" hook "env -C ../h-wt gh pr create"
expect "hook blocks env --chdir" 2 "another checkout" hook "env --chdir=../h-wt gh pr create --fill"
expect "hook joins continuation inside gh pr" 2 "$STALE_MSG" hook "$(printf 'gh pr \\\n  create --fill')"
expect "hook joins continuation after gh" 2 "$STALE_MSG" hook "$(printf 'gh \\\n  pr create --fill')"
mkdir -p ../h-wt/sub
expect "hook resolves the checkout from a subdirectory" 0 "" hook "gh pr create --fill" "$TEMP_DIR/h-wt/sub"
printf '%s' "$PAYLOAD" > utils/review-marker.py
expect "hook uses origin/main's marker script" 2 "$STALE_MSG" hook "gh pr create --fill"
not_run "hook with a tampered utils/review-marker.py"
git checkout -q utils/review-marker.py
GATE=$(git rev-parse origin/main) && git update-ref refs/remotes/origin/main "$PRE_GATE"
expect "hook allows while origin/main has no gate" 0 "" hook "gh pr create --fill"
git update-ref refs/remotes/origin/main "$GATE"
plant
expect "hook ignores stdlib-named files in the checkout" 2 "$STALE_MSG" hook "gh pr create --fill"
not_run "hook with planted argparse.py/subprocess.py"
unplant
git tag origin/main "$PRE_GATE"
expect "hook ignores a tag named origin/main" 2 "$STALE_MSG" hook "gh pr create --fill"
git tag -d origin/main >/dev/null

VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main expect "hook allows ready of a reviewed PR head" 0 "" \
  hook "gh pr ready 12"
VIEW_HEAD=wt VIEW_OID=$WT_STALE VIEW_BASE=main expect "hook checks the PR's remote head" 2 "is stale" \
  hook "gh pr ready 12"
VIEW_REPO=DataDog/java-profiler VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main expect "hook resolves ready selector past -R" 0 "" \
  hook "gh pr ready -R DataDog/java-profiler 12"
VIEW_REPO=DataDog/java-profiler VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main expect "hook resolves ready selector past --repo" 0 "" \
  hook "gh pr ready --repo DataDog/java-profiler 12"
VIEW_REPO=DataDog/java-profiler VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main expect "hook keeps -R given before pr" 0 "" \
  hook "gh -R DataDog/java-profiler pr ready 12"
VIEW_REPO=DataDog/java-profiler VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main expect "hook keeps --repo=" 0 "" \
  hook "gh pr ready 12 --repo=DataDog/java-profiler"
VIEW_HEAD=wt VIEW_OID=1234567890123456789012345678901234567890 VIEW_BASE=main \
  expect "hook reports an unfetched PR head" 2 "Rerunning the review will not help" hook "gh pr ready 12"
GH_FAIL=1 expect "hook blocks ready of a PR it cannot resolve" 2 "cannot resolve the PR" \
  hook "gh pr ready 12"
GH_FAIL=1 expect "hook checks the current branch for a bare ready" 2 "no review marker for branch feature" \
  hook "gh pr ready"
GH_FAIL=1 expect "bare ready falls back to a fresh current branch" 0 "" hook "gh pr ready" "$TEMP_DIR/h-wt"

marker write --tool t >/dev/null
expect "hook allows pr create when fresh" 0 "" hook "gh pr create --fill"
expect "hook allows a push before pr create" 0 "" hook "git push -u origin HEAD && gh pr create --fill"
expect "hook blocks a commit in the same command" 2 "changes git state" \
  hook "git commit -am more && git push -u origin HEAD && gh pr create --fill"
expect "hook blocks a branch switch in the same command" 2 "changes git state" \
  hook "git switch other && gh pr create --fill"
expect "hook allows matching --base" 0 "" hook "gh pr create --base main"
expect "hook allows an origin/-prefixed --base" 0 "" hook "gh pr create --base origin/main"
expect "hook blocks other --base" 2 "covered base origin/main, not origin/other" hook "gh pr create --base other"
expect "hook parses --base=" 2 "not origin/other" hook "gh pr create --base=other"
expect "hook parses compact -B" 2 "not origin/other" hook "gh pr create -Bother"
expect "hook finds --base after a heredoc body" 2 "not origin/other" \
  hook "$(printf "gh pr create --body \"\$(cat <<'EOF'\nIt's done\nEOF\n)\" \\\n  --base other")"
expect "hook blocks conflicting bases" 2 "several bases" hook "gh pr create --base main --base other"
DEFAULT_BRANCH=other expect "hook uses the repo default base without -B" 2 "not origin/other" \
  hook "gh pr create --fill"
DEFAULT_BRANCH=main expect "hook allows the matching default base" 0 "" hook "gh pr create --fill"
DEFAULT_BRANCH=other expect "hook prefers an explicit --base over the default" 0 "" \
  hook "gh pr create --base main"
git config branch.feature.gh-merge-base other
: > "$GH_LOG"
expect "hook honors branch gh-merge-base" 2 "not origin/other" hook "gh pr create --fill"
if grep -q "repo view" "$GH_LOG"; then fail "hook looked up the repo default despite gh-merge-base"; else pass; fi
git config branch.feature.gh-merge-base main
DEFAULT_BRANCH=other expect "gh-merge-base wins over the repo default" 0 "" hook "gh pr create --fill"
expect "explicit --base wins over gh-merge-base" 2 "not origin/other" hook "gh pr create --base other"
git config --unset branch.feature.gh-merge-base
git update-ref refs/remotes/origin/tmp origin/main && marker write --tool t --base origin/tmp >/dev/null
git update-ref -d refs/remotes/origin/tmp
expect "hook env error does not advise rerunning the review" 2 "Rerunning the review will not help" \
  hook "gh pr create"

# --- source checks in .githooks/pre-push, ticket check in the Claude Code hook ---
new_repo s
export OPEN_PRS=""
printf 'int x;\n' > bad.cpp && git add bad.cpp && git commit -qm bad
expect "pre-push skips source checks while origin/main lacks them" 0 "" \
  prepush "refs/heads/feature $(git rev-parse HEAD) refs/heads/feature $Z"
git checkout -q main
mkdir -p .github/scripts
cp "$ROOT/utils/check-copyright.py" "$ROOT/utils/check-claude-md.py" utils/
cp "$ROOT/.github/scripts/check_pr_ticket.py" .github/scripts/
python3 utils/check-claude-md.py --root . --write >/dev/null
git add . && git commit -qm "source checks" && git push -q origin main
git checkout -q feature && git rebase -q main
expect "pre-push blocks a new file without a copyright line" 1 "bad.cpp: new file has no" \
  prepush "refs/heads/feature $(git rev-parse HEAD) refs/heads/feature $Z"
printf '// Copyright 2026, Datadog, Inc.\nint x;\n' > bad.cpp && git commit -qam header
expect "pre-push allows a clean push" 0 "" \
  prepush "refs/heads/feature $(git rev-parse HEAD) refs/heads/feature $Z"
echo "## Build" >> CLAUDE.md && git commit -qam drift
expect "pre-push blocks a drifted CLAUDE.md" 1 "differs from the canonical stub" \
  prepush "refs/heads/feature $(git rev-parse HEAD) refs/heads/feature $Z"
git reset -q --hard HEAD~1
printf 'int y;\n' > dirty.cpp
expect "pre-push checks the pushed commit, not untracked files" 0 "" \
  prepush "refs/heads/feature $(git rev-parse HEAD) refs/heads/feature $Z"
rm dirty.cpp

# The copyright base follows the branch the push forks from, as CI follows the PR base.
git checkout -qb release/1.0 main
printf '// Copyright 2025, Datadog, Inc.\nint s;\n' > stale.cpp
git add stale.cpp && git commit -qm "earlier cherry-pick, stale header" && git push -q origin release/1.0
git checkout -qb backport release/1.0
printf '// Copyright 2026, Datadog, Inc.\nint b;\n' > backport.cpp && git add . && git commit -qm backport
expect "pre-push compares a backport with its release branch" 0 "" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $Z"
printf 'int n;\n' > nohdr.cpp && git add . && git commit -qm "no header"
expect "pre-push still blocks a violation in a backport's own commit" 1 "nohdr.cpp: new file has no" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $Z"
git config branch.backport.gh-merge-base release/9.9
expect "pre-push ignores an unfetched gh-merge-base" 1 "against origin/release/1.0" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $Z"
git reset -q --hard HEAD~1
git config branch.backport.gh-merge-base main
expect "pre-push honours the branch's gh-merge-base" 1 "stale.cpp: Datadog copyright ends in 2025" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $Z"
git config branch.backport.gh-merge-base origin/main
expect "pre-push names the base it compared with" 1 "against origin/main (set branch.backport.gh-merge-base" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $Z"
git config --unset branch.backport.gh-merge-base
git checkout -q main
printf '// Copyright 2025, Datadog, Inc.\nint m;\n' > mainstale.cpp
git add mainstale.cpp && git commit -qm "stale header on main" && git push -q origin main
git checkout -qb feature2 main
printf '// Copyright 2026, Datadog, Inc.\nint f;\n' > f2.cpp && git add . && git commit -qm f2
expect "pre-push compares a branch off main with main, not a release branch" 0 "" \
  prepush "refs/heads/feature2 $(git rev-parse HEAD) refs/heads/feature2 $Z"
# Forward port: release/1.1 has more own commits than main gained since its cut.
git checkout -qb release/1.1 main
for i in 1 2; do echo "fix $i" >> b.txt && git commit -qam "release fix $i"; done
git push -q origin release/1.1
git checkout -q main
printf '// Copyright 2025, Datadog, Inc.\nint m2;\n' > mainstale2.cpp
git add mainstale2.cpp && git commit -qm "stale header after the cut" && git push -q origin main
git checkout -qb forward main && git merge -q --no-ff -m "forward-port release/1.1" origin/release/1.1
expect "pre-push compares a forward port with main" 0 "" \
  prepush "refs/heads/forward $(git rev-parse HEAD) refs/heads/forward $Z"
git checkout -q feature

marker write --tool t >/dev/null
TICKET_MSG="reference no ticket"
expect "hook blocks pr create without a ticket" 2 "$TICKET_MSG" hook 'gh pr create --title "Fix" --body "Details"'
expect "hook allows a Jira key in the title" 0 "" hook 'gh pr create --title "Fix (PROF-1)" --body "Details"'
expect "hook allows short flags with a key" 0 "" hook 'gh pr create -t Fix -b "Refs PROF-3"'
expect "hook reads --flag=value forms" 2 "$TICKET_MSG" hook 'gh pr create --title=Fix --body=Details'
expect "hook reads attached short flags" 2 "$TICKET_MSG" hook 'gh pr create -tFix -bDetails'
expect "hook reads a body spanning lines" 0 "" hook $'gh pr create --title Fix --body "line one\nJIRA: PROF-5"'
printf 'Fixes #12\n' > body.md
expect "hook reads --body-file" 0 "" hook 'gh pr create --title Fix --body-file body.md'
printf 'no reference\n' > body.md
expect "hook blocks a --body-file without a ticket" 2 "$TICKET_MSG" hook 'gh pr create --title Fix -F body.md'
rm body.md
expect "hook blocks --fill when the commits have no ticket" 2 "$TICKET_MSG" hook 'gh pr create --fill'
expect "hook allows interactive pr create (CI checks it)" 0 "" hook 'gh pr create'
expect "hook allows a stdin body (CI checks it)" 0 "" hook 'gh pr create --title Fix --body-file -'
expect "hook allows a substituted body (CI checks it)" 0 "" hook 'gh pr create --title Fix --body "$(cat x)"'
expect "hook stops at the command separator" 2 "$TICKET_MSG" \
  hook 'gh pr create --title Fix --body x && gh issue create --title PROF-6'
git commit -q --allow-empty -m "Wire it up (PROF-7)" && marker write --tool t >/dev/null
expect "hook allows --fill when a commit has a ticket" 0 "" hook 'gh pr create --fill'
cd "$TEMP_DIR"

# --- .pi/extensions/require-fresh-review.ts (driven through a stub Pi API) ---
if node --experimental-strip-types --no-warnings -e "" >/dev/null 2>&1; then
  cat > "$TEMP_DIR/pi-driver.mjs" <<'EOF'
const [ext, cwd, toolName, command] = process.argv.slice(2);
const mod = await import(ext);
let handler;
mod.default({ on: (name, fn) => { if (name === "tool_call") handler = fn; } });
const result = await handler({ toolName, input: { command } }, { cwd });
if (result?.block) { console.error(result.reason); process.exit(2); }
EOF
  pi_hook() {
    node --experimental-strip-types --no-warnings "$TEMP_DIR/pi-driver.mjs" \
      "$PWD/.pi/extensions/require-fresh-review.ts" "${3:-$PWD}" "$1" "$2"
  }
  new_repo pi
  expect "pi adapter ignores other tools" 0 "" pi_hook read "gh pr create"
  expect "pi adapter ignores unrelated bash" 0 "" pi_hook bash "ls -la"
  expect "pi adapter blocks pr create without marker" 2 "Run the pre-pr-review skill" pi_hook bash "gh pr create --fill"
  expect "pi adapter allows a checkout without the hook" 0 "" pi_hook bash "gh pr create" "$TEMP_DIR/nogit"
  marker write --tool t >/dev/null
  expect "pi adapter allows pr create when fresh" 0 "" pi_hook bash "gh pr create --fill"
else
  echo "SKIP: pi adapter tests (node with --experimental-strip-types not found)"
fi

echo "$TESTS tests, $FAILED failed"
[ "$FAILED" -eq 0 ]
