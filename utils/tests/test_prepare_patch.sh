#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

# Test patch candidate discovery with local Git history and a GitHub CLI fixture.
# Run with: bash utils/tests/test_prepare_patch.sh

set -euo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT
export GIT_ALLOW_PROTOCOL=file

fail() {
  echo "FAIL: $*" >&2
  exit 1
}

mkdir "$TEMP_DIR/bin"
cat > "$TEMP_DIR/bin/gh" <<'EOF'
#!/usr/bin/env bash
set -euo pipefail
case "$*" in
  --version) echo "gh fixture" ;;
  'pr list --base main --state merged --limit 200 --json number,title,mergedAt,mergeCommit,labels')
    cat "$PR_FIXTURE"
    ;;
  *) echo "Unexpected gh command: $*" >&2; exit 1 ;;
esac
EOF
printf '#!/usr/bin/env bash\nexit 0\n' > "$TEMP_DIR/bin/clear"
chmod +x "$TEMP_DIR/bin/gh" "$TEMP_DIR/bin/clear"
export PATH="$TEMP_DIR/bin:$PATH"
export PR_FIXTURE="$TEMP_DIR/prs.json"
echo '[]' > "$PR_FIXTURE"

git init --bare --quiet "$TEMP_DIR/origin.git"
git --git-dir="$TEMP_DIR/origin.git" config core.hooksPath /dev/null
git init --quiet -b main "$TEMP_DIR/work"
cd "$TEMP_DIR/work"
git config user.name "Patch Test"
git config user.email "patch-test@example.invalid"
git config commit.gpgsign false
git config core.hooksPath /dev/null
git remote add origin "$TEMP_DIR/origin.git"
echo initial > file.txt
git add file.txt
git commit --quiet -m initial
BASE_SHA=$(git rev-parse HEAD)
git branch release/1.52._
git push --quiet origin main release/1.52._

check_candidates() {
  local expected=$1 output
  output=$(bash "$ROOT/utils/prepare-patch.sh" --branch release/1.52._ </dev/null 2>&1) ||
    fail "prepare-patch.sh failed: $output"
  [[ "$output" == *"$expected"* ]] ||
    fail "expected '$expected', got: $output"
  [ -z "$(git status --porcelain)" ] || fail "discovery changed the working tree"
  [ "$(git rev-parse --abbrev-ref HEAD)" = main ] || fail "discovery changed branches"
}

check_candidates "No commits on main ahead"

echo first >> file.txt
git commit --quiet -am first
FIRST_SHA=$(git rev-parse HEAD)
echo second >> file.txt
git commit --quiet -am second
SECOND_SHA=$(git rev-parse HEAD)
git push --quiet origin main
jq -n --arg base "$BASE_SHA" --arg first "$FIRST_SHA" --arg second "$SECOND_SHA" '
  [$base, $first, $second] | to_entries | map({
    number: (.key + 1), title: ("PR " + (.key | tostring)),
    mergedAt: "2026-10-26T00:00:00Z", mergeCommit: {oid: .value}, labels: []
  })
' > "$PR_FIXTURE"
check_candidates "Found 2 candidate PR(s)"

# A backport has a different SHA but the same patch, so Git marks it with '-'.
git checkout --quiet release/1.52._
git cherry-pick --quiet -x "$FIRST_SHA" >/dev/null
git push --quiet origin release/1.52._
git checkout --quiet main
check_candidates "Found 1 candidate PR(s)"

git checkout --quiet release/1.52._
git cherry-pick --quiet -x "$SECOND_SHA" >/dev/null
git push --quiet origin release/1.52._
git checkout --quiet main
check_candidates "No commits on main ahead"

echo "PASS: 4 patch candidate discovery cases"
