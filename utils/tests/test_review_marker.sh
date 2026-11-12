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

# gq <lastEdited> <headOid> <committed> -> raw GraphQL JSON for the description probe;
# pass an empty lastEdited to exercise the createdAt fallback.
gq() {
  le=null
  [ -n "$1" ] && le="\"$1\""
  printf '{"data":{"node":{"lastEditedAt":%s,"createdAt":"2018-01-01T00:00:00Z","headRefOid":"%s","commits":{"nodes":[{"commit":{"committedDate":"%s"}}]}}}}' "$le" "$2" "$3"
}

# gh stub, logging each call to $GH_LOG: `pr list --head B` reports an open PR when
# B is in $OPEN_PRS; `pr view <sel>` prints "$VIEW_ID $VIEW_NUMBER $VIEW_HEAD $VIEW_OID
# $VIEW_BASE" (VIEW_ID defaults to PRR_stub) unless <sel> looks like a repo (or $VIEW_REPO
# is set and not passed as -R); `repo view` prints $DEFAULT_BRANCH, or $OWNER_NAME for
# nameWithOwner; `api graphql` pipes $VIEW_GRAPHQL (raw JSON) through the command's --jq
# expression, only when -f i= matches $GRAPHQL_ID when that is set; `api repos/<name>`
# prints the fork-network root, <name> unless $NETWORK_ROOTS maps it ("name=root ..."),
# failing for $NAME_FAIL; $GH_FAIL fails all.
mkdir -p "$TEMP_DIR/bin" "$TEMP_DIR/oldgit" "$TEMP_DIR/nogh"
cat > "$TEMP_DIR/bin/gh" <<'EOF'
#!/bin/sh
echo "$*" >> "$GH_LOG"
[ -z "$GH_FAIL" ] || exit 1
case "$1 $2" in
  "pr list") for b in $OPEN_PRS; do [ "$b" = "$4" ] && { echo 1; exit 0; }; done
             echo 0; exit 0 ;;
  "pr view") url_repo=""
             case "$3" in
               https://github.com/*) url_repo=${3#https://github.com/}; url_repo=${url_repo%%/pull*} ;;
               */*) exit 1 ;;
             esac
             if [ -n "$VIEW_REPO" ]; then
               if [ -n "$url_repo" ]; then
                 [ "$url_repo" = "$VIEW_REPO" ] || exit 1
               else
                 case " $* " in *" -R $VIEW_REPO "*) ;; *) exit 1 ;; esac
               fi
             fi
             [ -n "$VIEW_ID" ] || VIEW_ID=PRR_stub
             [ -n "$VIEW_HEAD" ] && echo "$VIEW_ID $VIEW_NUMBER $VIEW_HEAD $VIEW_OID $VIEW_BASE" && exit 0; exit 1 ;;
  "api graphql") [ -n "$VIEW_GRAPHQL" ] || exit 1
                 if [ -n "$GRAPHQL_ID" ]; then
                   case "$*" in *"-f i=$GRAPHQL_ID"*) ;; *) exit 1 ;; esac
                 fi
                 jexpr="" prev=""
                 for a in "$@"; do [ "$prev" = "--jq" ] && { jexpr=$a; break; }; prev=$a; done
                 if [ -n "$jexpr" ]; then printf '%s' "$VIEW_GRAPHQL" | jq -r "$jexpr"
                 else echo "$VIEW_GRAPHQL"; fi
                 exit 0 ;;
  "repo view") case "$*" in
                 *nameWithOwner*) [ -n "$OWNER_NAME" ] && echo "$OWNER_NAME" && exit 0; exit 1 ;;
                 *) [ -n "$DEFAULT_BRANCH" ] && echo "$DEFAULT_BRANCH" && exit 0; exit 1 ;;
               esac ;;
  "api repos/"*) name=${2#repos/}
                 [ "$name" = "$NAME_FAIL" ] && exit 1
                 for pair in $NETWORK_ROOTS; do [ "${pair%%=*}" = "$name" ] && name=${pair#*=}; done
                 echo "$name"; exit 0 ;;
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
export OPEN_PRS="" VIEW_HEAD="" VIEW_OID="" VIEW_BASE="" VIEW_REPO="" GH_FAIL="" DEFAULT_BRANCH="" NAME_FAIL="" NETWORK_ROOTS="" GRAPHQL_ID=""
export VIEW_NUMBER="" VIEW_ID="" VIEW_GRAPHQL="" OWNER_NAME=""

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
# R: a nonzero stand-in for an existing remote ref's sha; the all-zero id means the
# push creates the remote ref, which pre-push treats as having no open PR.
R=1111111111111111111111111111111111111111
TIP=$(git rev-parse HEAD)
Z=0000000000000000000000000000000000000000
export OPEN_PRS="feature"
expect "pre-push blocks open-PR branch without marker" 1 "Run the pre-pr-review skill" \
  prepush "refs/heads/feature $TIP refs/heads/feature $R"
expect "pre-push allows deletion" 0 "" prepush "(delete) $Z refs/heads/feature $TIP"
expect "pre-push allows a SHA-256 deletion" 0 "" \
  prepush "(delete) ${Z}${Z:0:24} refs/heads/feature $TIP"
: > "$GH_LOG"
expect "pre-push allows tags" 0 "" prepush "refs/tags/v1 $TIP refs/tags/v1 $Z"
if grep -q "pr list" "$GH_LOG"; then fail "pre-push gated a tag push (asked gh about it)"; else pass; fi
OPEN_PRS="" expect "pre-push allows branch without open PR" 0 "" \
  prepush "refs/heads/feature $TIP refs/heads/feature $R"
GH_FAIL=1 expect "pre-push fails open when gh fails" 0 "" \
  prepush "refs/heads/feature $TIP refs/heads/feature $R"
PATH="$TEMP_DIR/nogh:/usr/bin:/bin" expect "pre-push fails open when gh cannot run" 0 "" \
  sh -c "printf '%s\n' 'refs/heads/feature $TIP refs/heads/feature $R' | $PY .githooks/pre-push"
marker write --tool t >/dev/null
: > "$GH_LOG"
expect "pre-push warns to re-verify the description on an open-PR push" 0 \
  "re-verify its title and description" prepush "refs/heads/feature $TIP refs/heads/feature $R"
if grep -q "pr list" "$GH_LOG"; then pass; else fail "pre-push did not probe the open PR: $(cat "$GH_LOG")"; fi
OPEN_PRS="" expect "pre-push stays silent without an open PR" 0 "" \
  prepush "refs/heads/feature $TIP refs/heads/feature $R"
: > "$GH_LOG"
OPEN_PRS="feature" expect "pre-push skips the probe for a remote ref being created" 0 "" \
  prepush "refs/heads/newbr $TIP refs/heads/newbr $Z"
if grep -q "pr list" "$GH_LOG"; then fail "pre-push probed a created remote ref: $(cat "$GH_LOG")"; else pass; fi
git checkout -qb feature2
marker write --tool t >/dev/null
git checkout -q feature
OPEN_PRS="feature feature2"
expect "pre-push defers the warning until the push is decided" 0 "re-verify its title and description" \
  prepush "refs/heads/feature $TIP refs/heads/feature $R
refs/heads/feature2 $TIP refs/heads/feature2 $R"
echo more >> b.txt && git commit -qam more
STALE=$(git rev-parse HEAD)
expect "pre-push blocks unreviewed tip" 1 "is stale" \
  prepush "refs/heads/feature $STALE refs/heads/feature $R"
OPEN_PRS=""
if prepush "refs/heads/feature $STALE refs/heads/feature $R" 2>"$TEMP_DIR/err2"; then
  pass
else
  fail "pre-push blocked a failing check without an open PR: $(cat "$TEMP_DIR/err2")"
fi
if grep -qF "has an open PR" "$TEMP_DIR/err2"; then
  fail "pre-push blamed an open PR for a plain check failure: $(cat "$TEMP_DIR/err2")"
else
  pass
fi
OPEN_PRS="feature feature2"
if prepush "refs/heads/feature $STALE refs/heads/feature $R
refs/heads/feature2 $TIP refs/heads/feature2 $R" 2>"$TEMP_DIR/err3"; then
  fail "pre-push allowed a push with a blocked ref"
else
  pass
fi
if grep -qF "re-verify its title" "$TEMP_DIR/err3"; then
  fail "pre-push warned about a ref it blocked anyway: $(cat "$TEMP_DIR/err3")"
else
  pass
fi
export OPEN_PRS="feature"
printf '%s' "$PAYLOAD" > utils/review-marker.py
expect "pre-push uses origin/main's marker script" 1 "is stale" \
  prepush "refs/heads/feature $STALE refs/heads/feature $R"
not_run "pre-push with a tampered utils/review-marker.py"
git checkout -q utils/review-marker.py
GATE=$(git rev-parse origin/main) && git update-ref refs/remotes/origin/main "$PRE_GATE"
expect "pre-push allows while origin/main has no gate" 0 "" \
  prepush "refs/heads/feature $STALE refs/heads/feature $R"
git update-ref refs/remotes/origin/main "$GATE"
plant
expect "pre-push ignores stdlib-named files in the checkout" 1 "is stale" \
  prepush "refs/heads/feature $STALE refs/heads/feature $R"
not_run "pre-push with planted argparse.py/subprocess.py"
unplant
git tag origin/main "$PRE_GATE"
expect "pre-push ignores a tag named origin/main" 1 "is stale" \
  prepush "refs/heads/feature $STALE refs/heads/feature $R"
git tag -d origin/main >/dev/null
expect "pre-push gates \`git push origin HEAD\`" 1 "is stale" \
  prepush "HEAD $STALE refs/heads/feature $R"
git tag feature HEAD
expect "pre-push HEAD refspec beside a same-named tag" 1 "is stale" \
  prepush "HEAD $STALE refs/heads/feature $R"
git tag -d feature >/dev/null
expect "pre-push gates \`git push origin <sha>:feature\`" 1 "is stale" \
  prepush "$STALE $STALE refs/heads/feature $R"
git checkout -q --detach "$TIP"
expect "pre-push on detached HEAD uses the remote branch's marker" 0 "" \
  prepush "HEAD $TIP refs/heads/feature $R"
git checkout -q feature

# The current branch (side) has no marker; only feature's marker can make this pass.
git checkout -qb side
expect "pre-push checks the pushed branch, not the current one" 0 "" \
  prepush "refs/heads/feature $TIP refs/heads/feature $R"
git checkout -q feature

git update-ref refs/remotes/origin/tmp origin/main
git reset -q --hard "$TIP" && marker write --tool t --base origin/tmp >/dev/null
git update-ref -d refs/remotes/origin/tmp
expect "pre-push env error says how to proceed" 1 "push with --no-verify" \
  prepush "refs/heads/feature $TIP refs/heads/feature $R"
marker write --tool t >/dev/null

marker install-hook >/dev/null
git push -q origin feature  # create the remote ref: the next push updates it, with a real remote sha
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
# A plain gh pr call that certainly targets another repository is not this repo's policy.
expect "hook gates --repo while a remote is not on GitHub" 2 "$STALE_MSG" \
  hook "gh pr create --repo DataDog/speedlab --fill"
git remote set-url origin https://github.com/DataDog/java-profiler.git
expect "hook allows --repo naming another repository" 0 "" \
  hook "gh pr create --repo DataDog/speedlab --head topic --fill"
expect "hook allows -R before pr naming another repository" 0 "" hook "gh -R DataDog/speedlab pr ready 105"
expect "hook allows ready by another repository's PR URL" 0 "" \
  hook "gh pr ready https://github.com/DataDog/speedlab/pull/105"
expect "hook gates --repo naming this repository" 2 "$STALE_MSG" hook "gh pr create --repo datadog/JAVA-profiler --fill"
expect "hook gates a repository spelled other than OWNER/REPO" 2 "$STALE_MSG" \
  hook "gh pr create --repo github.com/DataDog/speedlab --fill"
expect "hook gates -R of an earlier command" 2 "$STALE_MSG" \
  hook "gh repo view -R DataDog/speedlab && gh pr create --fill"
expect "hook gates two repository flags" 2 "$STALE_MSG" \
  hook "gh pr create -R DataDog/speedlab -R DataDog/java-profiler --fill"
expect "hook gates an attached -R value" 2 "$STALE_MSG" \
  hook "gh pr create --title -RDataDog/speedlab --body x"
expect "hook does not read another flag's value as -R" 2 "$STALE_MSG" \
  hook "gh pr create --title -R DataDog/speedlab --fill"
expect "hook gates -R split off by carriage returns" 2 "$STALE_MSG" \
  hook "$(printf 'gh pr create --title=x\r-R\rDataDog/speedlab --fill')"
expect "hook gates -R split off by backslash-newlines" 2 "$STALE_MSG" \
  hook "$(printf 'gh pr create --title=x\\\n-R\\\nDataDog/speedlab --fill')"
NETWORK_ROOTS="datadog/old-profiler=datadog/java-profiler" \
  expect "hook gates a renamed name of this repository" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/old-profiler --head topic --fill"
GH_FAIL=1 expect "hook gates another repository it cannot resolve" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/speedlab --head topic --fill"
NAME_FAIL=datadog/java-profiler expect "hook gates when a remote cannot be resolved" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/speedlab --head topic --fill"
expect "hook gates a quoted --" 2 "cannot resolve the PR" hook "gh pr ready --repo DataDog/speedlab \"--\" 105"
expect "hook gates a short-flag cluster" 2 "$STALE_MSG" hook "gh pr create -dt -RDataDog/speedlab --body x"
expect "hook gates -R in a comment" 2 "$STALE_MSG" hook "gh pr create --fill # -R DataDog/speedlab"
expect "hook gates -R as a redirection target" 2 "$STALE_MSG" \
  hook "gh pr create --fill -R DataDog/speedlab 2> -RDataDog/x"
expect "hook gates a process substitution" 2 "cannot resolve the PR" \
  hook "gh pr ready https://github.com/DataDog/speedlab/pull/1 <(gh pr create --fill)"
expect "hook gates GH_REPO" 2 "$STALE_MSG" hook "GH_REPO=DataDog/speedlab gh pr create --fill"
expect "hook gates a variable" 2 "$STALE_MSG" hook 'gh pr create --repo $REPO --fill'
expect "hook gates a scheme-less PR URL" 2 "cannot resolve the PR" \
  hook "gh pr ready github.com/DataDog/speedlab/pull/1"
expect "hook gates this repository's PR URL despite -R" 2 "cannot resolve the PR" \
  hook "gh -R DataDog/speedlab pr ready https://github.com/DataDog/java-profiler/pull/9"
expect "hook gates this repository's command next to another's" 2 "cannot resolve the PR" \
  hook "gh pr ready 1 --repo DataDog/speedlab && gh pr create --fill"
expect "hook still blocks a cd into another repository" 2 "another checkout" \
  hook "cd $TEMP_DIR/elsewhere && gh pr create --repo DataDog/speedlab --fill"
git remote set-url origin https://github.com/someone/java-profiler.git
expect "hook gates upstream from a fork checkout" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/java-profiler --head someone:topic --fill"
git remote set-url origin https://github.com/someone/my-fork.git
NETWORK_ROOTS="someone/my-fork=datadog/java-profiler" \
  expect "hook gates upstream from a differently named fork" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/java-profiler --head someone:topic --fill"
NETWORK_ROOTS="someone/my-fork=datadog/java-profiler" \
  expect "hook gates upstream's PR URL from a differently named fork" 2 "cannot resolve the PR" \
  hook "gh pr ready https://github.com/DataDog/java-profiler/pull/9"
git remote set-url origin https://github.com/someone/fork-of-fork.git
NETWORK_ROOTS="someone/fork-of-fork=datadog/java-profiler" \
  expect "hook gates upstream from a fork of a fork" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/java-profiler --head someone:topic --fill"
git remote set-url origin https://github.com/acme/widget.git
git config url.https://github.com/DataDog/java-profiler.git.insteadOf https://github.com/acme/widget.git
expect "hook judges the URL git uses after insteadOf" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/java-profiler --head topic --fill"
git config --unset url.https://github.com/DataDog/java-profiler.git.insteadOf
git config remote.origin.pushurl https://github.com/DataDog/java-profiler.git
expect "hook judges push URLs" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/java-profiler --head topic --fill"
git config --unset remote.origin.pushurl
git config --add remote.origin.url https://github.com/DataDog/java-profiler.git
expect "hook judges every fetch URL" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/java-profiler --head topic --fill"
git config --unset remote.origin.url https://github.com/DataDog/java-profiler.git
git config url.https://github.com/DataDog/java-profiler.git.pushInsteadOf https://github.com/acme/widget.git
expect "hook judges the push URL after pushInsteadOf" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/java-profiler --head topic --fill"
git config --unset url.https://github.com/DataDog/java-profiler.git.pushInsteadOf
expect "hook gates DataDog/java-profiler from a mirror-only checkout" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/java-profiler --head topic --fill"
NETWORK_ROOTS="datadog/jp-renamed=datadog/java-profiler" \
  expect "hook gates this repository's network from a mirror-only checkout" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/jp-renamed --head topic --fill"
expect "hook gates an empty quoted argument" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/speedlab --head topic --title \"\" --fill"
expect "hook gates an unknown flag" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/speedlab --head topic --no-maintainer-edit --fill"
git remote set-url origin git@github-work:DataDog/java-profiler.git
git remote add other https://github.com/someone/elsewhere.git
expect "hook gates when a remote URL is not plainly GitHub's" 2 "--head names a branch" \
  hook "gh pr create --repo DataDog/java-profiler --head topic --fill"
git remote remove other
git remote set-url origin "$TEMP_DIR/h-origin.git"
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

VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main expect "hook allows ready of a reviewed PR head" 0 "" \
  hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_STALE VIEW_BASE=main expect "hook checks the PR's remote head" 2 "is stale" \
  hook "gh pr ready 12"
VIEW_REPO=DataDog/java-profiler VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main expect "hook resolves ready selector past -R" 0 "" \
  hook "gh pr ready -R DataDog/java-profiler 12"
VIEW_REPO=DataDog/java-profiler VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main expect "hook resolves ready selector past --repo" 0 "" \
  hook "gh pr ready --repo DataDog/java-profiler 12"
VIEW_REPO=DataDog/java-profiler VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main expect "hook keeps -R given before pr" 0 "" \
  hook "gh -R DataDog/java-profiler pr ready 12"
VIEW_REPO=DataDog/java-profiler VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main expect "hook keeps --repo=" 0 "" \
  hook "gh pr ready 12 --repo=DataDog/java-profiler"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=1234567890123456789012345678901234567890 VIEW_BASE=main \
  expect "hook reports an unfetched PR head" 2 "Rerunning the review will not help" hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_GRAPHQL="$(gq 2019-06-01T00:00:00Z $WT_TIP 2020-01-01T00:00:00Z)" \
  expect "hook blocks ready when the description predates the head commit" 2 "last edited before" \
  hook "gh pr ready 12"
VIEW_REPO=DataDog/java-profiler VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_ID=PRR_url GRAPHQL_ID=PRR_url VIEW_GRAPHQL="$(gq 2019-06-01T00:00:00Z $WT_TIP 2020-01-01T00:00:00Z)" \
  expect "hook probes the PR gh resolved, not -R's repository" 2 "last edited before" \
  hook "gh -R DataDog/speedlab pr ready https://github.com/DataDog/java-profiler/pull/12"
VIEW_REPO=DataDog/java-profiler VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_ID=PRR_url GRAPHQL_ID=PRR_url VIEW_GRAPHQL="$(gq 2019-06-01T00:00:00Z $WT_TIP 2020-01-01T00:00:00Z)" \
  expect "hook probes the PR gh resolved past a URL path fragment" 2 "last edited before" \
  hook "gh -R DataDog/speedlab pr ready https://github.com/DataDog/java-profiler/pull/12/files"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_STALE VIEW_BASE=main VIEW_GRAPHQL="$(gq 2019-06-01T00:00:00Z $WT_STALE 2020-01-01T00:00:00Z)" \
  expect "hook reports the stale marker, not the description, when the check fails" 2 "$STALE_MSG" \
  hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_GRAPHQL="$(gq 2020-01-01T00:00:00Z $WT_TIP 2020-01-01T00:00:00Z)" \
  expect "hook allows ready when the description is as fresh as the head commit" 0 "" hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_GRAPHQL="$(gq 2021-06-01T00:00:00Z $WT_TIP 2020-01-01T00:00:00Z)" \
  expect "hook allows ready when the description postdates the head commit" 0 "" hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_GRAPHQL="$(gq "" $WT_TIP 2020-01-01T00:00:00Z)" \
  expect "hook blocks via createdAt when the body was never edited" 2 "last edited before" \
  hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_GRAPHQL="$(gq 2019-06-01T00:00:00Z $WT_STALE 2020-01-01T00:00:00Z)" \
  expect "hook fails open when the PR moved between the two gh calls" 0 "" hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_GRAPHQL="$(gq 2019-06-01T00:00:00Z $WT_TIP 2030-01-01T00:00:00Z)" \
  expect "hook fails open when the head commit is dated in the future" 0 "" hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_GRAPHQL="$(gq 2019-06-01T00:00:00 $WT_TIP 2020-01-01T00:00:00Z)" \
  expect "hook fails open when the description timestamp lacks a UTC designator" 0 "" hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main \
  expect "hook fails open when the description probe fails" 0 "" hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_GRAPHQL="$(gq not-a-date $WT_TIP 2020-01-01T00:00:00Z)" \
  expect "hook fails open when the description timestamp is unparseable" 0 "" hook "gh pr ready 12"
VIEW_NUMBER=12 VIEW_HEAD=wt VIEW_OID=$WT_TIP VIEW_BASE=main VIEW_GRAPHQL='{"data":{"node":{"lastEditedAt":"2019-06-01T00:00:00Z","createdAt":"2018-01-01T00:00:00Z","headRefOid":"$WT_TIP","commits":{"nodes":[]}}}}' \
  expect "hook fails open when the PR has no commits" 0 "" hook "gh pr ready 12"
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
# The fixtures' copyright years are literals, so pin the commit dates they are judged by.
export GIT_AUTHOR_DATE=2026-03-01T12:00:00+00:00 GIT_COMMITTER_DATE=2026-03-01T12:00:00+00:00
new_repo s
export OPEN_PRS=""
printf 'int x;\n' > bad.cpp && git add bad.cpp && git commit -qm bad
expect "pre-push skips source checks while origin/main lacks them" 0 "" \
  prepush "refs/heads/feature $(git rev-parse HEAD) refs/heads/feature $R"
git checkout -q main
mkdir -p .github/scripts
cp "$ROOT/utils/check-copyright.py" "$ROOT/utils/check-claude-md.py" utils/
cp "$ROOT/.github/scripts/check_pr_ticket.py" .github/scripts/
python3 utils/check-claude-md.py --root . --write >/dev/null
git add . && git commit -qm "source checks" && git push -q origin main
git checkout -q feature && git rebase -q main
expect "pre-push blocks a new file without a copyright line" 1 "bad.cpp: new file has no" \
  prepush "refs/heads/feature $(git rev-parse HEAD) refs/heads/feature $R"
printf '// Copyright 2026, Datadog, Inc.\nint x;\n' > bad.cpp && git commit -qam header
expect "pre-push allows a clean push" 0 "" \
  prepush "refs/heads/feature $(git rev-parse HEAD) refs/heads/feature $R"
echo "## Build" >> CLAUDE.md && git commit -qam drift
expect "pre-push blocks a drifted CLAUDE.md" 1 "differs from the canonical stub" \
  prepush "refs/heads/feature $(git rev-parse HEAD) refs/heads/feature $R"
git reset -q --hard HEAD~1
printf 'int y;\n' > dirty.cpp
expect "pre-push checks the pushed commit, not untracked files" 0 "" \
  prepush "refs/heads/feature $(git rev-parse HEAD) refs/heads/feature $R"
rm dirty.cpp

# The copyright base follows the branch the push forks from, as CI follows the PR base.
git checkout -qb release/1.0 main
printf '// Copyright 2025, Datadog, Inc.\nint s;\n' > stale.cpp
git add stale.cpp && git commit -qm "earlier cherry-pick, stale header" && git push -q origin release/1.0
git checkout -qb backport release/1.0
printf '// Copyright 2026, Datadog, Inc.\nint b;\n' > backport.cpp && git add . && git commit -qm backport
expect "pre-push compares a backport with its release branch" 0 "" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $R"
printf 'int n;\n' > nohdr.cpp && git add . && git commit -qm "no header"
expect "pre-push still blocks a violation in a backport's own commit" 1 "nohdr.cpp: new file has no" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $R"
expect "pre-push names the detected base and its override" 1 \
  "against origin/release/1.0 (set branch.backport.gh-merge-base to change)" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $R"
git config branch.backport.gh-merge-base release/9.9
expect "pre-push ignores an unfetched gh-merge-base and says so" 1 \
  "against origin/release/1.0 (gh-merge-base origin/release/9.9 is not fetched" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $R"
git reset -q --hard HEAD~1
git config branch.backport.gh-merge-base main
expect "pre-push honours the branch's gh-merge-base" 1 "stale.cpp: Datadog copyright ends in 2025" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $R"
git config branch.backport.gh-merge-base origin/main
expect "pre-push names a configured base" 1 "against origin/main (from branch.backport.gh-merge-base)" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $R"
git update-ref refs/remotes/origin/orphan "$(git commit-tree 4b825dc642cb6eb9a060e54bf8d69288fbee4904 -m orphan)"
git config branch.backport.gh-merge-base orphan
expect "pre-push names the base when the check is skipped" 0 \
  "check-copyright.py against origin/orphan (from branch.backport.gh-merge-base) skipped" \
  prepush "refs/heads/backport $(git rev-parse HEAD) refs/heads/backport $R"
git update-ref -d refs/remotes/origin/orphan
git config --unset branch.backport.gh-merge-base
git checkout -q main
printf '// Copyright 2025, Datadog, Inc.\nint m;\n' > mainstale.cpp
git add mainstale.cpp && git commit -qm "stale header on main" && git push -q origin main
git checkout -qb feature2 main
printf '// Copyright 2026, Datadog, Inc.\nint f;\n' > f2.cpp && git add . && git commit -qm f2
expect "pre-push compares a branch off main with main, not a release branch" 0 "" \
  prepush "refs/heads/feature2 $(git rev-parse HEAD) refs/heads/feature2 $R"
# Forward port: release/1.1 has more own commits than main gained since its cut.
git checkout -qb release/1.1 main
for i in 1 2; do echo "fix $i" >> b.txt && git commit -qam "release fix $i"; done
git push -q origin release/1.1
git checkout -q main
printf '// Copyright 2025, Datadog, Inc.\nint m2;\n' > mainstale2.cpp
git add mainstale2.cpp && git commit -qm "stale header after the cut" && git push -q origin main
git checkout -qb forward main && git merge -q --no-ff -m "forward-port release/1.1" origin/release/1.1
expect "pre-push compares a forward port with main" 0 "" \
  prepush "refs/heads/forward $(git rev-parse HEAD) refs/heads/forward $R"
git checkout -q feature

marker write --tool t >/dev/null
TICKET_MSG="reference no ticket"
export DEFAULT_BRANCH=main  # fill text is judged only when the base is known
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
expect "hook lets --body-file override --body" 2 "$TICKET_MSG" \
  hook 'gh pr create --title Fix --body PROF-1 -F body.md'
rm body.md
expect "hook uses the last --body, as gh does" 2 "$TICKET_MSG" \
  hook 'gh pr create --title Fix --body PROF-1 --body Details'
expect "hook blocks --fill when the commits have no ticket" 2 "$TICKET_MSG" hook 'gh pr create --fill'
expect "hook leaves other fill spellings to CI" 0 "" hook 'gh pr create -df'
expect "hook leaves two fill flags to CI" 0 "" hook 'gh pr create --fill --fill-verbose'
DEFAULT_BRANCH="" expect "hook leaves --fill to CI when the base is unknown" 0 "" hook 'gh pr create --fill'
git commit -q --allow-empty -m "Rename foo" -m 'Calls `bar()` now.' && marker write --tool t >/dev/null
expect "hook checks commit text that contains backticks" 2 "$TICKET_MSG" hook 'gh pr create --fill-verbose'
git checkout -qb side && git commit -q --allow-empty -m "Side work" && git checkout -q feature
git merge -q --no-ff -m "Merge side (PROF-11)" side && git branch -qD side && marker write --tool t >/dev/null
expect "hook skips merge commits, as gh does" 2 "$TICKET_MSG" hook 'gh pr create --fill'
expect "hook stops at a comment" 2 "$TICKET_MSG" hook 'gh pr create --title Fix --body x # --title PROF-1'
expect "hook allows a quoted body that starts with #" 0 "" \
  hook $'gh pr create --title "Add X" --body "## What\nJira: PROF-1"'
expect "hook never reads a value as a flag" 0 "" hook 'gh pr create --title "PROF-1 fix" --body "-the details"'
expect "hook leaves --dry-run to CI" 0 "" hook 'gh pr create --dry-run --title Fix --body x'
expect "hook leaves --web to CI" 0 "" hook 'gh pr create --web --title Fix --body x'
expect "hook leaves --dry-run=true to CI" 0 "" hook 'gh pr create --dry-run=true --title Fix --body x'
expect "hook leaves --editor=true to CI" 0 "" hook 'gh pr create --editor=true --title Fix --body x'
expect "hook leaves combined -de to CI" 0 "" hook 'gh pr create -de --title Fix --body x'
expect "hook judges a --draft PR" 2 "$TICKET_MSG" hook 'gh pr create --draft --title Fix --body x'
expect "hook judges a -d PR" 2 "$TICKET_MSG" hook 'gh pr create -d --title Fix --body x'
expect "hook judges a command with 2>&1" 2 "$TICKET_MSG" hook 'gh pr create --title Fix --body x 2>&1'
expect "hook judges a command with 2>/dev/null" 2 "$TICKET_MSG" hook 'gh pr create --title Fix --body x 2>/dev/null'
expect "hook leaves --recover to CI" 0 "" hook 'gh pr create --recover f.json --title Fix --body x'
git commit -q --allow-empty -m "Café work" && marker write --tool t >/dev/null
git config i18n.logOutputEncoding ISO-8859-1
expect "hook reads non-UTF-8 commit text" 2 "$TICKET_MSG" hook 'gh pr create --fill-verbose'
git config --unset i18n.logOutputEncoding
expect "hook stops at merged operators" 2 "$TICKET_MSG" hook 'gh pr create --title Fix --body x);gh x --title PROF-6'
expect "hook does not cut at a # inside a word" 0 "" \
  hook 'gh pr create --title Fix --body wip#1 --title PROF-13'
expect "hook allows interactive pr create (CI checks it)" 0 "" hook 'gh pr create'
expect "hook allows a prompted body (CI checks it)" 0 "" hook 'gh pr create --title Fix'
expect "hook allows a prompted title (CI checks it)" 0 "" hook 'gh pr create --body Details'
expect "hook allows a stdin body (CI checks it)" 0 "" hook 'gh pr create --title Fix --body-file -'
expect "hook allows a substituted body (CI checks it)" 0 "" hook 'gh pr create --title Fix --body "$(cat x)"'
expect "hook allows shell variables (CI checks them)" 0 "" hook 'gh pr create --title "$TITLE" --body "$BODY"'
printf 'no reference\n' > body.md
expect "hook ignores a substituted --body that --body-file overrides" 2 "$TICKET_MSG" \
  hook 'gh pr create --title Fix --body "$(cat x)" -F body.md'
rm body.md
expect "hook stops at the command separator" 2 "$TICKET_MSG" \
  hook 'gh pr create --title Fix --body x && gh issue create --title PROF-6'
expect "hook stops at an unquoted newline" 2 "$TICKET_MSG" \
  hook $'gh pr create --title Fix --body x\ngh pr create --title PROF-6 --body y'
expect "hook stops at ; before a newline" 2 "$TICKET_MSG" \
  hook $'gh pr create --title Fix --body x;\ngh pr create --title PROF-6 --body y'
expect "hook stops at && before a newline" 2 "$TICKET_MSG" \
  hook $'gh pr create --title Fix --body x &&\ngh pr create --title PROF-6 --body y'
expect "hook stops at a blank line" 2 "$TICKET_MSG" \
  hook $'gh pr create --title Fix --body x\n\ngh pr create --title PROF-6 --body y'
expect "hook stops at a trailing comment" 2 "$TICKET_MSG" \
  hook $'gh pr create --title Fix --body x # note\ngh pr create --title PROF-6 --body y'
git commit -q --allow-empty -m "Body-only ticket" -m "Refs PROF-8" && marker write --tool t >/dev/null
expect "hook reads only subjects for a multi-commit --fill" 2 "$TICKET_MSG" hook 'gh pr create --fill'
expect "hook reads bodies for --fill-verbose" 0 "" hook 'gh pr create --fill-verbose'
git branch -m feature PROF-9-fix && marker write --tool t >/dev/null
expect "hook humanizes the branch name for a multi-commit --fill title" 2 "$TICKET_MSG" \
  hook 'gh pr create --fill'
git branch -m PROF-9-fix feature
git commit -q --allow-empty -m "Wire it up (PROF-7)" && marker write --tool t >/dev/null
expect "hook allows --fill when a commit has a ticket" 0 "" hook 'gh pr create --fill'
expect "hook lets explicit --title and --body override --fill" 2 "$TICKET_MSG" \
  hook 'gh pr create --fill --title Fix --body Details'
expect "hook reads only the first commit for --fill-first" 2 "$TICKET_MSG" hook 'gh pr create --fill-first'
git update-ref refs/remotes/origin/tbase HEAD~1 && marker write --tool t --base origin/tbase >/dev/null
expect "hook reads commits since --base for --fill-first" 0 "" \
  hook 'gh pr create --fill-first --base tbase'
git update-ref -d refs/remotes/origin/tbase
git update-ref refs/remotes/origin/tbase HEAD~1 && marker write --tool t --base origin/tbase >/dev/null
DEFAULT_BRANCH=tbase expect "hook uses the repo default branch as the fill base" 0 "" \
  hook 'gh pr create --fill-first'
git update-ref -d refs/remotes/origin/tbase
export DEFAULT_BRANCH=""
unset GIT_AUTHOR_DATE GIT_COMMITTER_DATE
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
