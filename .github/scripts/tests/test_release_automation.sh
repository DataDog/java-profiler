#!/usr/bin/env bash

set -euo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)
VALIDATOR="$ROOT/.github/scripts/validate-release-bump.sh"
TRIVIAL_VALIDATOR="$ROOT/.github/scripts/validate-trivial-approval.sh"
TEMP_DIR=$(mktemp -d)
TESTS=0

cleanup() {
  rm -rf "$TEMP_DIR"
}
trap cleanup EXIT

fail() {
  echo "FAIL: $*" >&2
  exit 1
}

pass() {
  TESTS=$((TESTS + 1))
}

write_valid_fixture() {
  local path=$1
  local parent='plugins {
    java
}

version = "1.48.0-SNAPSHOT"
'
  local head='plugins {
    java
}

version = "1.49.0-SNAPSHOT"
'
  jq -n \
    --arg repo "DataDog/java-profiler" \
    --arg sender_permission "write" \
    --arg author_login "release-engineer" \
    --arg author_type "User" \
    --arg author_permission "write" \
    --arg state "open" \
    --arg title "[Automated] Bump dev version to 1.49.0" \
    --arg base_ref "main" \
    --arg base_sha "$(printf 'c%.0s' {1..40})" \
    --arg head_ref "automated/bump-1-49-0" \
    --arg head_sha "$(printf 'b%.0s' {1..40})" \
    --arg head_repo "DataDog/java-profiler" \
    --arg parent_sha "$(printf 'a%.0s' {1..40})" \
    --arg parent_build "$parent" \
    --arg head_build "$head" \
    '{
      repo: $repo,
      sender_permission: $sender_permission,
      author_login: $author_login,
      author_type: $author_type,
      author_permission: $author_permission,
      state: $state,
      draft: false,
      title: $title,
      base_ref: $base_ref,
      base_sha: $base_sha,
      head_ref: $head_ref,
      head_sha: $head_sha,
      current_head_sha: $head_sha,
      head_repo: $head_repo,
      labels: ["trivial"],
      changed_files: [{filename: "build.gradle.kts", status: "modified"}],
      head_parents: [$parent_sha],
      parent_sha: $parent_sha,
      parent_reachable: true,
      parent_build: $parent_build,
      head_build: $head_build
    }' > "$path"
}

expect_success() {
  local fixture=$1
  shift
  "$VALIDATOR" --fixture "$fixture" "$@" >/dev/null ||
    fail "expected validation success for $fixture"
  pass
}

expect_failure() {
  local fixture=$1
  shift
  if "$VALIDATOR" --fixture "$fixture" "$@" >/dev/null 2>&1; then
    fail "expected validation failure for $fixture"
  fi
  pass
}

write_labeler_fixture() {
  local path=$1
  local actor=$2
  local permission=$3
  local actor_type=$4
  jq -n --arg actor "$actor" --arg permission "$permission" \
    --arg actor_type "$actor_type" \
    '{actor: $actor, permission: $permission, actor_type: $actor_type}' > "$path"
}

expect_trivial_success() {
  local actor=$1
  local permission=$2
  local fixture="$TEMP_DIR/trivial-$actor.json"
  local actor_type=${3:-User}
  write_labeler_fixture "$fixture" "$actor" "$permission" "$actor_type"
  "$TRIVIAL_VALIDATOR" --actor "$actor" --actor-type "$actor_type" \
    --fixture "$fixture" >/dev/null ||
    fail "expected trivial approval authorization for $actor/$permission"
  pass
}

expect_trivial_failure() {
  local actor=$1
  local permission=$2
  local fixture="$TEMP_DIR/trivial-$actor.json"
  local actor_type=${3:-User}
  write_labeler_fixture "$fixture" "$actor" "$permission" "$actor_type"
  if "$TRIVIAL_VALIDATOR" --actor "$actor" --actor-type "$actor_type" \
    --fixture "$fixture" >/dev/null 2>&1; then
    fail "expected trivial approval rejection for $actor/$permission"
  fi
  pass
}

expect_trivial_success release-engineer write
expect_trivial_success release-maintainer maintain
expect_trivial_success repository-admin admin
expect_trivial_success 'dependabot[bot]' read Bot
expect_trivial_success 'dd-octo-sts[bot]' read Bot
expect_trivial_failure contributor triage
expect_trivial_failure unknown-user read
expect_trivial_failure 'unknown[bot]' admin Bot

VALID="$TEMP_DIR/valid.json"
write_valid_fixture "$VALID"
expect_success "$VALID"
expect_success "$VALID" \
  --source-sha "$(printf 'a%.0s' {1..40})" \
  --expected-head-sha "$(printf 'b%.0s' {1..40})"

MAINTAIN="$TEMP_DIR/maintain.json"
jq '.sender_permission = "maintain" | .author_permission = "maintain"' \
  "$VALID" > "$MAINTAIN"
expect_success "$MAINTAIN"

PATCH="$TEMP_DIR/patch.json"
jq '
  .base_ref = "release/1.48._" |
  .head_ref = "automated/bump-1-48-1" |
  .title = "[Automated] Bump dev version to 1.48.1" |
  .head_build |= sub("1.49.0"; "1.48.1")
' "$VALID" > "$PATCH"
expect_success "$PATCH"

ROLLOVER="$TEMP_DIR/rollover.json"
jq '
  .parent_build |= sub("1.48.0"; "1.99.0") |
  .head_build |= sub("1.49.0"; "2.0.0") |
  .head_ref = "automated/bump-2-0-0" |
  .title = "[Automated] Bump dev version to 2.0.0"
' "$VALID" > "$ROLLOVER"
expect_success "$ROLLOVER"

STS_BOT="$TEMP_DIR/sts-bot.json"
jq '
  .author_login = "dd-octo-sts[bot]" |
  .author_type = "Bot"
' "$VALID" > "$STS_BOT"
expect_success "$STS_BOT"

BRANCH="$TEMP_DIR/branch.json"
jq '.expected_head_sha = .head_sha' "$VALID" > "$BRANCH"
expect_success "$BRANCH" --branch

declare -a MUTATIONS=(
  '.sender_permission = "read"'
  '.author_permission = "read"'
  '.author_type = "Bot"'
  '.draft = true'
  '.state = "closed"'
  '.base_ref = "feature"'
  '.head_ref = "attacker/bump-1-49-0"'
  '.head_repo = "attacker/java-profiler"'
  '.labels = []'
  '.changed_files += [{filename: "payload", status: "added"}]'
  '.head_parents += ["dddddddddddddddddddddddddddddddddddddddd"]'
  '.parent_reachable = false'
  '.current_head_sha = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"'
  '.title = "Looks harmless"'
  '.head_build |= sub("1.49.0"; "1.50.0")'
  '.head_build += "malicious = true\n"'
  '.head_build |= rtrimstr("\n")'
)

for index in "${!MUTATIONS[@]}"; do
  fixture="$TEMP_DIR/invalid-$index.json"
  jq "${MUTATIONS[$index]}" "$VALID" > "$fixture"
  expect_failure "$fixture"
done

WRONG_PARENT="$TEMP_DIR/wrong-parent.json"
jq '.parent_sha = "ffffffffffffffffffffffffffffffffffffffff"' \
  "$VALID" > "$WRONG_PARENT"
expect_failure "$WRONG_PARENT"

WRONG_HEAD="$TEMP_DIR/wrong-head.json"
jq '.expected_head_sha = "ffffffffffffffffffffffffffffffffffffffff"' \
  "$VALID" > "$WRONG_HEAD"
expect_failure "$WRONG_HEAD" --branch

WRONG_SERIES="$TEMP_DIR/wrong-series.json"
jq '
  .base_ref = "release/1.47._" |
  .head_ref = "automated/bump-1-48-1" |
  .title = "[Automated] Bump dev version to 1.48.1" |
  .head_build |= sub("1.49.0"; "1.48.1")
' "$VALID" > "$WRONG_SERIES"
expect_failure "$WRONG_SERIES"

NETWORK_DIR="$TEMP_DIR/no-network"
mkdir "$NETWORK_DIR"
NETWORK_MARKER="$NETWORK_DIR/gh-was-called"
printf '#!/usr/bin/env bash\n: > "%s"\nexit 99\n' "$NETWORK_MARKER" \
  > "$NETWORK_DIR/gh"
chmod +x "$NETWORK_DIR/gh"
PATH="$NETWORK_DIR:/usr/bin:/bin" "$VALIDATOR" --fixture "$VALID" >/dev/null ||
  fail "fixture validation failed with a fail-closed gh stub"
[ ! -e "$NETWORK_MARKER" ] || fail "fixture validation invoked gh"
pass

RELEASE_SCRIPT=$(<"$ROOT/.github/scripts/release.sh")
VALIDATOR_SCRIPT=$(<"$ROOT/.github/scripts/validate-release-bump.sh")
TRIVIAL_VALIDATOR_SCRIPT=$(<"$TRIVIAL_VALIDATOR")
[[ "$TRIVIAL_VALIDATOR_SCRIPT" == *'dependabot\[bot\]|dd-octo-sts\[bot\]'* ]] ||
  fail "trivial validator does not use the trusted bot allowlist"
[[ "$TRIVIAL_VALIDATOR_SCRIPT" == *"write|maintain|admin"* ]] ||
  fail "trivial validator does not accept trusted human permissions"
pass
[[ "$VALIDATOR_SCRIPT" == *'LABEL="trivial"'* ]] ||
  fail "validator does not use the trivial label"
[[ "$RELEASE_SCRIPT" == *"gh pr create"* ]] || fail "release job does not create a PR"
[[ "$RELEASE_SCRIPT" == *"gh pr edit"* ]] || fail "release job does not label a PR"
[[ "$RELEASE_SCRIPT" == *"gh pr merge"* ]] || fail "release job does not merge a PR"
[[ "$RELEASE_SCRIPT" == *"BUMP_PR_TOKEN"* ]] || fail "release job does not accept a PR token"
[[ "$RELEASE_SCRIPT" == *'--add-label "trivial"'* ]] ||
  fail "release job does not use the trivial label"
[[ "$RELEASE_SCRIPT" != *"release-version-bump"* ]] ||
  fail "release job uses an unrecognized release label"
pass

FINALIZER=$(<"$ROOT/utils/finalize-release-bump.sh")
grep -Fq -- "--match-head-commit \"\$EXPECTED_HEAD_SHA\"" <<<"$FINALIZER" ||
  fail "finalizer is not SHA locked"
[[ "$FINALIZER" != *"--auto"* ]] || fail "finalizer enables queued auto-merge"
[[ "$FINALIZER" != *"--admin"* ]] || fail "finalizer bypasses branch protection"
[[ "$FINALIZER" == *"validate-release-bump.sh"* ]] ||
  fail "finalizer does not use the shared validator"
[[ "$FINALIZER" == *'LABEL="trivial"'* ]] ||
  fail "finalizer does not use the trivial label"
[[ "$FINALIZER" != *"gh label create"* ]] ||
  fail "finalizer creates a release-specific label"
pass

APPROVAL_WORKFLOW=$(<"$ROOT/.github/workflows/approve-trivial.yml")
VALIDATION_LINE=$(grep -n "Validate release bump before approval" \
  <<<"$APPROVAL_WORKFLOW" | cut -d: -f1)
FEDERATION_LINE=$(grep -n "uses: DataDog/dd-octo-sts-action" \
  <<<"$APPROVAL_WORKFLOW" | cut -d: -f1)
REVALIDATION_LINE=$(grep -n "Revalidate release bump immediately before approval" \
  <<<"$APPROVAL_WORKFLOW" | cut -d: -f1)
[ "$VALIDATION_LINE" -lt "$FEDERATION_LINE" ] ||
  fail "approval token is federated before validation"
[ "$FEDERATION_LINE" -lt "$REVALIDATION_LINE" ] ||
  fail "approval token is federated after the final validation"
[[ "$APPROVAL_WORKFLOW" == *"github.event.label.name == 'trivial'"* ]] ||
  fail "approval workflow does not trigger on trivial"
[[ "$APPROVAL_WORKFLOW" == *"github.event.sender.login"* ]] ||
  fail "approval workflow does not use the label event sender"
AUTHORIZATION_LINE=$(grep -n "Authorize trivial labeler" \
  <<<"$APPROVAL_WORKFLOW" | cut -d: -f1)
[ "$AUTHORIZATION_LINE" -lt "$FEDERATION_LINE" ] ||
  fail "STS token is federated before labeler authorization"
[[ "$APPROVAL_WORKFLOW" == *"steps.classify.outputs.release_bump == 'true'"* ]] ||
  fail "approval workflow does not conditionally validate release bumps"
[[ "$APPROVAL_WORKFLOW" == *"commit_id: process.env.EXPECTED_HEAD_SHA"* ]] ||
  fail "approval is not pinned to the validated SHA"
pass

RELEASE_WORKFLOW=$(<"$ROOT/.github/workflows/release-validated.yml")
APPROVAL_POLICY=$(<"$ROOT/.github/chainguard/self.approve-trivial.approve-pr.sts.yaml")
[[ "$APPROVAL_POLICY" == *"refs/heads/(main|release/[0-9]+\\.[0-9]+\\._)"* ]] ||
  fail "approval policy does not allow protected release branches"
pass
[ "$(grep -Fc "inputs.dry_run != true && inputs.release_type != 'retag'" \
  <<<"$RELEASE_WORKFLOW")" -ge 2 ] ||
  fail "dry run can produce a finalization manifest"
[[ "$RELEASE_WORKFLOW" == *"BUMP_PR_TOKEN"* ]] ||
  fail "release workflow does not provide the scoped PR token"
[[ "$RELEASE_WORKFLOW" == *"self.release-bump.create-pr"* ]] ||
  fail "release workflow does not federate the scoped PR token"
grep -Fq "GITHUB_SHA\" != \"\$EXPECTED_SOURCE_SHA" <<<"$RELEASE_WORKFLOW" ||
  fail "release dispatch is not locked to the requested source SHA"
pass

# Run the release script against a filesystem-backed bare remote. The gh and
# validator stubs enforce the command contract without network access.
REMOTE="$TEMP_DIR/remote.git"
WORK="$TEMP_DIR/work"
FAKE_BIN="$TEMP_DIR/bin"
mkdir "$FAKE_BIN"
git init --bare --quiet "$REMOTE"
git init --quiet -b main "$WORK"
mkdir -p "$WORK/.github/scripts"
cp "$ROOT/.github/scripts/release.sh" "$WORK/.github/scripts/release.sh"
cat > "$WORK/.github/scripts/validate-release-bump.sh" <<'VALIDATOR'
#!/usr/bin/env bash
set -euo pipefail
echo "$*" >> "$VALIDATOR_CALLS"
VALIDATOR
chmod +x "$WORK/.github/scripts/validate-release-bump.sh"
printf 'version = "1.48.0-SNAPSHOT"\n' > "$WORK/build.gradle.kts"
cat > "$WORK/gradlew" <<'GRADLE'
#!/usr/bin/env bash
set -euo pipefail
version=$(sed -nE 's/^version = "([0-9]+\.[0-9]+\.[0-9]+)-SNAPSHOT"$/\1/p' build.gradle.kts)
IFS=. read -r major minor patch <<<"$version"
case "$*" in
  "printVersion -Psnapshot=false")
    echo "Version: $version"
    ;;
  "incrementVersion --versionIncrementType=MINOR")
    if [ "$minor" -ge 99 ]; then
      major=$((major + 1))
      minor=0
    else
      minor=$((minor + 1))
    fi
    patch=0
    printf 'version = "%s.%s.%s-SNAPSHOT"\n' "$major" "$minor" "$patch" > build.gradle.kts
    ;;
  "incrementVersion --versionIncrementType=MAJOR")
    major=$((major + 1))
    minor=0
    patch=0
    printf 'version = "%s.%s.%s-SNAPSHOT"\n' "$major" "$minor" "$patch" > build.gradle.kts
    ;;
  "incrementVersion --versionIncrementType=PATCH")
    patch=$((patch + 1))
    printf 'version = "%s.%s.%s-SNAPSHOT"\n' "$major" "$minor" "$patch" > build.gradle.kts
    ;;
  *)
    echo "unsupported fake Gradle call: $*" >&2
    exit 1
    ;;
esac
GRADLE
chmod +x "$WORK/gradlew" "$WORK/.github/scripts/release.sh"
cat > "$FAKE_BIN/gh" <<'GH'
#!/usr/bin/env bash
set -euo pipefail
echo "$*" >> "$GH_CALLS"
STATE=""
[ ! -f "$GH_STATE" ] || STATE=$(<"$GH_STATE")

if [ "$1" = "pr" ] && [ "$2" = "create" ]; then
  [ -z "$STATE" ] || { echo "PR already exists" >&2; exit 1; }
  echo created > "$GH_STATE"
  echo "https://github.invalid/DataDog/java-profiler/pull/1"
  exit 0
fi

if [ "$1" = "pr" ] && [ "$2" = "edit" ]; then
  [ "$STATE" = "created" ] || { echo "PR was not created" >&2; exit 1; }
  case "$*" in
    *"--add-label trivial"*) ;;
    *) echo "unexpected label operation: $*" >&2; exit 1 ;;
  esac
  echo labeled > "$GH_STATE"
  exit 0
fi

if [ "$1" = "pr" ] && [ "$2" = "merge" ]; then
  [ "$STATE" = "labeled" ] || { echo "PR was not labeled" >&2; exit 1; }
  MATCH_SHA=""
  shift 2
  while [ "$#" -gt 0 ]; do
    case "$1" in
      --match-head-commit) MATCH_SHA=${2:-}; shift 2 ;;
      --auto) shift ;;
      *) shift ;;
    esac
  done
  ACTUAL_SHA=$(git --git-dir="$GH_REMOTE" rev-parse "refs/heads/$GH_BUMP_REF")
  [ -n "$MATCH_SHA" ] || { echo "merge was not SHA pinned" >&2; exit 1; }
  [ "$MATCH_SHA" = "$ACTUAL_SHA" ] || {
    echo "merge SHA does not match the bump branch" >&2
    exit 1
  }
  echo merged > "$GH_STATE"
  exit 0
fi

echo "unsupported fake gh command: $*" >&2
exit 1
GH
chmod +x "$FAKE_BIN/gh"
git -C "$WORK" config user.name "Release Test"
git -C "$WORK" config user.email "release-test@example.invalid"
git -C "$WORK" config commit.gpgsign false
git -C "$WORK" config tag.gpgsign false
git -C "$WORK" config core.hooksPath /dev/null
git -C "$WORK" add .
git -C "$WORK" commit --quiet -m initial
SOURCE_SHA=$(git -C "$WORK" rev-parse HEAD)
git -C "$WORK" remote add origin "$REMOTE"
git -C "$WORK" push --quiet -u origin main
(
  cd "$WORK"
  GITHUB_OUTPUT="$TEMP_DIR/release-outputs" GH_CALLS="$TEMP_DIR/gh-calls" \
    GH_STATE="$TEMP_DIR/gh-state" GH_REMOTE="$REMOTE" GH_BUMP_REF=automated/bump-1-49-0 \
    VALIDATOR_CALLS="$TEMP_DIR/validator-calls" GITHUB_REPOSITORY=DataDog/java-profiler \
    GITHUB_ACTOR=release-engineer GITHUB_TOKEN=token BUMP_PR_TOKEN=token PATH="$FAKE_BIN:$PATH" \
    ./.github/scripts/release.sh MINOR
) >"$TEMP_DIR/release.log" 2>&1 || {
    tail -20 "$TEMP_DIR/release.log" >&2
    fail "release script failed against the local bare remote"
  }
BUMP_SHA=$(git --git-dir="$REMOTE" rev-parse refs/heads/automated/bump-1-49-0)
grep -Fq -- "pr create" "$TEMP_DIR/gh-calls" || fail "release script did not create a PR"
grep -Fq -- "pr edit" "$TEMP_DIR/gh-calls" || fail "release script did not label the PR"
grep -Fq -- "pr merge" "$TEMP_DIR/gh-calls" || fail "release script did not merge the PR"
grep -Fq -- "--auto" "$TEMP_DIR/gh-calls" || fail "release script did not queue auto-merge"
grep -Fq -- "--match-head-commit $BUMP_SHA" "$TEMP_DIR/gh-calls" ||
  fail "release script did not pin auto-merge to the bump SHA"
grep -Fq -- "--pr-number 1" "$TEMP_DIR/validator-calls" ||
  fail "release script did not validate the created PR before merging"
grep -Fq -- "--expected-head-sha $BUMP_SHA" "$TEMP_DIR/validator-calls" ||
  fail "final PR validation did not pin the bump SHA"
[ "$(<"$TEMP_DIR/gh-state")" = "merged" ] ||
  fail "fake GitHub PR did not complete the create-label-merge sequence"
[ "$(git --git-dir="$REMOTE" rev-parse "$BUMP_SHA^")" = "$SOURCE_SHA" ] ||
  fail "bump commit parent differs from the release source"
git --git-dir="$REMOTE" show-ref --verify --quiet refs/heads/release/1.48._ ||
  fail "release branch was not pushed"
git --git-dir="$REMOTE" show-ref --verify --quiet refs/tags/v_1.48.0 ||
  fail "release tag was not pushed"
grep -Fqx "source_sha=$SOURCE_SHA" "$TEMP_DIR/release-outputs" ||
  fail "release outputs omitted source SHA"
grep -Fqx "bump_head_sha=$BUMP_SHA" "$TEMP_DIR/release-outputs" ||
  fail "release outputs omitted bump SHA"
pass

# Verify major releases keep the release commit in main before creating the
# next-version bump. This exercises the ancestry invariant used by the
# validator: 2.0.0 -> 2.1.0, rather than 1.48.0 -> 2.1.0.
MAJOR_REMOTE="$TEMP_DIR/major-remote.git"
MAJOR_WORK="$TEMP_DIR/major-work"
MAJOR_BIN="$TEMP_DIR/major-bin"
mkdir "$MAJOR_BIN"
git init --bare --quiet "$MAJOR_REMOTE"
git init --quiet -b main "$MAJOR_WORK"
mkdir -p "$MAJOR_WORK/.github/scripts"
cp "$ROOT/.github/scripts/release.sh" "$MAJOR_WORK/.github/scripts/release.sh"
cp "$WORK/.github/scripts/validate-release-bump.sh" "$MAJOR_WORK/.github/scripts/validate-release-bump.sh"
printf 'version = "1.48.0-SNAPSHOT"\n' > "$MAJOR_WORK/build.gradle.kts"
cp "$WORK/gradlew" "$MAJOR_WORK/gradlew"
chmod +x "$MAJOR_WORK/.github/scripts/release.sh"
cp "$FAKE_BIN/gh" "$MAJOR_BIN/gh"
chmod +x "$MAJOR_BIN/gh"
git -C "$MAJOR_WORK" config user.name "Release Test"
git -C "$MAJOR_WORK" config user.email "release-test@example.invalid"
git -C "$MAJOR_WORK" config commit.gpgsign false
git -C "$MAJOR_WORK" config tag.gpgsign false
git -C "$MAJOR_WORK" config core.hooksPath /dev/null
git -C "$MAJOR_WORK" add .
git -C "$MAJOR_WORK" commit --quiet -m initial
MAJOR_INITIAL_SHA=$(git -C "$MAJOR_WORK" rev-parse HEAD)
git -C "$MAJOR_WORK" remote add origin "$MAJOR_REMOTE"
git -C "$MAJOR_WORK" push --quiet -u origin main
(
  cd "$MAJOR_WORK"
  GITHUB_OUTPUT="$TEMP_DIR/major-outputs" GH_CALLS="$TEMP_DIR/major-gh-calls" \
    GH_STATE="$TEMP_DIR/major-gh-state" GH_REMOTE="$MAJOR_REMOTE" GH_BUMP_REF=automated/bump-2-1-0 \
    VALIDATOR_CALLS="$TEMP_DIR/major-validator-calls" GITHUB_REPOSITORY=DataDog/java-profiler \
    GITHUB_ACTOR=release-engineer GITHUB_TOKEN=token BUMP_PR_TOKEN=token PATH="$MAJOR_BIN:$PATH" \
    ./.github/scripts/release.sh MAJOR
) >"$TEMP_DIR/major-release.log" 2>&1 || {
    tail -20 "$TEMP_DIR/major-release.log" >&2
    fail "major release script failed against the local bare remote"
  }
grep -Fq -- "pr merge" "$TEMP_DIR/major-gh-calls" ||
  fail "major release script did not queue auto-merge"
[ "$(<"$TEMP_DIR/major-gh-state")" = "merged" ] ||
  fail "major fake GitHub PR did not complete the create-label-merge sequence"
MAJOR_RELEASE_SHA=$(git --git-dir="$MAJOR_REMOTE" rev-parse refs/heads/main)
MAJOR_BUMP_SHA=$(git --git-dir="$MAJOR_REMOTE" rev-parse refs/heads/automated/bump-2-1-0)
[ "$(git --git-dir="$MAJOR_REMOTE" show "$MAJOR_RELEASE_SHA:build.gradle.kts")" = \
  'version = "2.0.0-SNAPSHOT"' ] ||
  fail "main does not contain the major release version"
[ "$(git --git-dir="$MAJOR_REMOTE" rev-parse "$MAJOR_BUMP_SHA^")" = "$MAJOR_RELEASE_SHA" ] ||
  fail "major bump parent is not the release commit"
[ "$(git --git-dir="$MAJOR_REMOTE" rev-parse refs/heads/release/2.0._)" = "$MAJOR_RELEASE_SHA" ] ||
  fail "major release branch differs from main"
[ "$(git --git-dir="$MAJOR_REMOTE" rev-parse 'refs/tags/v_2.0.0^{commit}')" = "$MAJOR_RELEASE_SHA" ] ||
  fail "major release tag does not point to the release commit"
grep -Fqx "source_sha=$MAJOR_RELEASE_SHA" "$TEMP_DIR/major-outputs" ||
  fail "major release outputs omitted the release commit SHA"
[ "$MAJOR_RELEASE_SHA" != "$MAJOR_INITIAL_SHA" ] ||
  fail "major release did not create a release commit"
pass

echo "PASS: $TESTS hermetic release-automation test groups"
