#!/usr/bin/env bash

set -euo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)
VALIDATOR="$ROOT/.github/scripts/validate-release-bump.sh"
TRIVIAL_VALIDATOR="$ROOT/.github/scripts/validate-trivial-approval.sh"
WAITER="$ROOT/.github/scripts/wait-release-bump.sh"
TEMP_DIR=$(mktemp -d)
TESTS=0

# This suite must never mutate GitHub or any other network remote. Restrict Git
# to filesystem transports and shadow every network-capable command used by the
# release automation. Individual integration scenarios prepend their own gh
# fixture, while every unexpected network command fails immediately.
export GIT_ALLOW_PROTOCOL=file
NETWORK_GUARD_BIN="$TEMP_DIR/network-guard-bin"
mkdir "$NETWORK_GUARD_BIN"
for command in gh ssh scp curl wget; do
  printf '%s\n' \
    '#!/usr/bin/env bash' \
    "echo \"network command blocked by hermetic release test: \${0##*/}\" >&2" \
    'exit 97' > "$NETWORK_GUARD_BIN/$command"
  chmod +x "$NETWORK_GUARD_BIN/$command"
done
PATH="$NETWORK_GUARD_BIN:$PATH"
export PATH

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
    --arg sender_login "dd-octo-sts[bot]" \
    --arg sender_type "Bot" \
    --arg sender_permission "none" \
    --arg author_login "github-actions[bot]" \
    --arg author_type "Bot" \
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
      sender_login: $sender_login,
      sender_type: $sender_type,
      sender_permission: $sender_permission,
      author_login: $author_login,
      author_type: $author_type,
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

if PERMISSION_ERROR=$("$TRIVIAL_VALIDATOR" \
    --actor unavailable-user --actor-type User 2>&1); then
  fail "trivial validator accepted an actor after permission lookup failure"
fi
[ "$PERMISSION_ERROR" = \
  "trivial approval validation failed: unable to determine repository permission for label actor unavailable-user" ] ||
  fail "trivial validator did not normalize permission lookup failure"
pass

VALID="$TEMP_DIR/valid.json"
write_valid_fixture "$VALID"
expect_success "$VALID"
expect_success "$VALID" \
  --source-sha "$(printf 'a%.0s' {1..40})" \
  --expected-head-sha "$(printf 'b%.0s' {1..40})"

HUMAN_LABELER="$TEMP_DIR/human-labeler.json"
jq '.sender_login = "release-engineer" | .sender_type = "User" | .sender_permission = "maintain"' \
  "$VALID" > "$HUMAN_LABELER"
expect_success "$HUMAN_LABELER"

PATCH="$TEMP_DIR/patch.json"
jq '
  .base_ref = "release/1.48._" |
  .head_ref = "automated/bump-1-48-1" |
  .title = "[Automated] Bump dev version to 1.48.1" |
  .head_build |= sub("1.49.0"; "1.48.1")
' "$VALID" > "$PATCH"
expect_success "$PATCH"

FIRST_PATCH="$TEMP_DIR/first-patch.json"
jq \
  --arg source_sha "$(printf 'a%.0s' {1..40})" \
  --arg release_sha "$(printf 'd%.0s' {1..40})" \
  '
    .base_ref = "release/1.48._" |
    .base_sha = $release_sha |
    .head_ref = "automated/bump-1-48-2" |
    .title = "[Automated] Bump dev version to 1.48.2" |
    .parent_sha = $release_sha |
    .head_parents = [$release_sha] |
    .parent_build |= sub("1.48.0"; "1.48.1") |
    .head_build |= sub("1.49.0"; "1.48.2") |
    .source_sha = $source_sha |
    .source_build = (.parent_build | sub("1.48.1"; "1.48.0")) |
    .release_tag_sha = $release_sha |
    .release_tag_annotated = true |
    .release_parents = [$source_sha] |
    .release_changed_files = [{filename: "build.gradle.kts", status: "modified"}] |
    .source_tag_annotated = true |
    .source_tag_reachable = true
  ' "$VALID" > "$FIRST_PATCH"
expect_success "$FIRST_PATCH" --branch --first-patch \
  --source-sha "$(printf 'a%.0s' {1..40})" \
  --expected-head-sha "$(printf 'b%.0s' {1..40})" \
  --local-release-tag v_1.48.1

declare -a FIRST_PATCH_MUTATIONS=(
  '.release_tag_annotated = false'
  '.release_tag_sha = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"'
  '.release_parents = ["eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"]'
  '.release_changed_files += [{filename: "payload", status: "added"}]'
  '.source_tag_annotated = false'
  '.source_tag_reachable = false'
  '.source_build |= sub("1.48.0"; "1.48.1")'
  '.parent_build += "malicious = true\n"'
)
for index in "${!FIRST_PATCH_MUTATIONS[@]}"; do
  fixture="$TEMP_DIR/invalid-first-patch-$index.json"
  jq "${FIRST_PATCH_MUTATIONS[$index]}" "$FIRST_PATCH" > "$fixture"
  expect_failure "$fixture" --branch --first-patch \
    --source-sha "$(printf 'a%.0s' {1..40})" \
    --expected-head-sha "$(printf 'b%.0s' {1..40})" \
    --local-release-tag v_1.48.1
done

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
expect_failure "$STS_BOT"

HUMAN_AUTHOR="$TEMP_DIR/human-author.json"
jq '.author_login = "release-engineer" | .author_type = "User"' \
  "$VALID" > "$HUMAN_AUTHOR"
expect_failure "$HUMAN_AUTHOR"

MAJOR="$TEMP_DIR/major.json"
jq \
  --arg release_sha "$(printf 'd%.0s' {1..40})" \
  '
    .head_ref = "automated/bump-2-1-0" |
    .title = "[Automated] Bump dev version to 2.1.0" |
    .head_build |= sub("1.49.0"; "2.1.0") |
    .release_ref_sha = $release_sha |
    .release_tag_sha = $release_sha |
    .release_tag_annotated = true |
    .release_parents = [.parent_sha] |
    .release_changed_files = [{filename: "build.gradle.kts", status: "modified"}] |
    .release_build = (.parent_build | sub("1.48.0"; "2.0.0"))
  ' "$VALID" > "$MAJOR"
expect_success "$MAJOR"

declare -a MAJOR_MUTATIONS=(
  '.release_tag_annotated = false'
  '.release_tag_sha = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"'
  '.release_parents = ["eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"]'
  '.release_changed_files += [{filename: "payload", status: "added"}]'
  '.release_build |= sub("2.0.0"; "2.0.1")'
  '.release_build += "malicious = true\n"'
  '.head_build |= sub("2.1.0"; "3.1.0")'
)
for index in "${!MAJOR_MUTATIONS[@]}"; do
  fixture="$TEMP_DIR/invalid-major-$index.json"
  jq "${MAJOR_MUTATIONS[$index]}" "$MAJOR" > "$fixture"
  expect_failure "$fixture"
done

BRANCH="$TEMP_DIR/branch.json"
jq '.expected_head_sha = .head_sha | .source_sha = .parent_sha' "$VALID" > "$BRANCH"
expect_success "$BRANCH" --branch \
  --source-sha "$(printf 'a%.0s' {1..40})" \
  --expected-head-sha "$(printf 'b%.0s' {1..40})"

declare -a MUTATIONS=(
  '.sender_login = "unknown[bot]"'
  '.sender_type = "User" | .sender_permission = "read"'
  '.author_login = "unknown[bot]"'
  '.author_type = "User"'
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
expect_failure "$WRONG_HEAD" --branch \
  --source-sha "$(printf 'a%.0s' {1..40})" \
  --expected-head-sha "$(printf 'b%.0s' {1..40})"

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
[[ "$RELEASE_SCRIPT" != *"set -x"* ]] ||
  fail "release script enables credential-bearing shell tracing"
[[ "$VALIDATOR_SCRIPT" == *'github-actions[bot]'* ]] ||
  fail "validator does not require the GitHub Actions PR author"
[[ "$VALIDATOR_SCRIPT" == *'dd-octo-sts[bot]'* ]] ||
  fail "validator does not require the distinct STS labeler"
[[ "$RELEASE_SCRIPT" == *"GH_TOKEN=\"\$GITHUB_TOKEN\" gh api --method POST"* ]] ||
  fail "release job does not create the PR with GITHUB_TOKEN"
[[ "$RELEASE_SCRIPT" == *"GH_TOKEN=\"\$BUMP_LABEL_TOKEN\" gh api --method POST"* ]] ||
  fail "release job does not label the PR with the distinct STS token"
[[ "$RELEASE_SCRIPT" != *"gh pr merge"* ]] ||
  fail "release script can merge before approval and selected CI pass"
[[ "$RELEASE_SCRIPT" == *"git commit --amend"* ]] ||
  fail "release job does not produce the CI-triggering synchronize update"
[[ "$RELEASE_SCRIPT" == *"--branch"* ]] || fail "release job does not validate the bump branch"
[[ "$RELEASE_SCRIPT" != *"release-version-bump"* ]] ||
  fail "release job uses an unrecognized release label"
pass

[ ! -e "$ROOT/utils/finalize-release-bump.sh" ] ||
  fail "obsolete human release-bump finalizer still exists"
WAITER_SCRIPT=$(<"$WAITER")
[[ "$WAITER_SCRIPT" == *'dd-octo-sts[bot]'* ]] ||
  fail "waiter does not require the STS approval"
[[ "$WAITER_SCRIPT" == *'--check)'* ]] ||
  fail "waiter does not accept explicit check names"
[[ "$WAITER_SCRIPT" != *'--required'* ]] ||
  fail "waiter still depends on repository-required checks"
[[ "$WAITER_SCRIPT" == *'RELEASE_BUMP_POLL_ATTEMPTS:-360'* ]] ||
  fail "waiter default does not allow 30 minutes for selected CI"
[[ "$WAITER_SCRIPT" == *'gh pr merge'* ]] ||
  fail "waiter does not merge after its gates"
[[ "$WAITER_SCRIPT" == *'--match-head-commit'* ]] ||
  fail "waiter merge is not SHA locked"
[[ "$WAITER_SCRIPT" == *"merged_at"* ]] ||
  fail "waiter does not verify the PR actually merged"
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
CI_WORKFLOW=$(<"$ROOT/.github/workflows/ci.yml")
APPROVAL_POLICY=$(<"$ROOT/.github/chainguard/self.approve-trivial.approve-pr.sts.yaml")
EXPECTED_APPROVAL_WORKFLOW_REF='job_workflow_ref: DataDog/java-profiler/\.github/workflows/approve-trivial\.yml@refs/heads/(main|release/[0-9]+\.[0-9]+\._)'
grep -Fqx "  $EXPECTED_APPROVAL_WORKFLOW_REF" <<<"$APPROVAL_POLICY" ||
  fail "approval policy workflow identity does not allow protected release branches"
pass
[ ! -e "$ROOT/.github/chainguard/self.release-bump.create-pr.sts.yaml" ] ||
  fail "obsolete release PR token policy still exists"
[ -e "$ROOT/.github/chainguard/self.release-bump.label-pr.sts.yaml" ] ||
  fail "release bump label policy is missing"
[[ "$RELEASE_WORKFLOW" == *"self.release-bump.label-pr"* ]] ||
  fail "release workflow does not federate the label-only token"
[[ "$RELEASE_WORKFLOW" == *"wait-release-bump.sh"* ]] ||
  fail "release workflow does not run the gated merger"
[[ "$RELEASE_WORKFLOW" == *"--check release-bump-ci"* ]] ||
  fail "release workflow does not select the aggregate release-bump CI check"
[[ "$CI_WORKFLOW" == *"release-bump-ci:"* ]] ||
  fail "CI workflow does not provide the selected release-bump check"
[[ "$CI_WORKFLOW" == *"needs: [release-automation-tests, check-formatting, check-javadoc, test-matrix]"* ]] ||
  fail "release-bump CI check does not aggregate the selected jobs"
[[ "$RELEASE_WORKFLOW" != *"finalize-release-bump.sh"* ]] ||
  fail "release workflow still references the human finalizer"
grep -Fq "GITHUB_SHA\" != \"\$EXPECTED_SOURCE_SHA" <<<"$RELEASE_WORKFLOW" ||
  fail "release dispatch is not locked to the requested source SHA"
[[ "$RELEASE_WORKFLOW" == *"FIRST_PATCH=false"* ]] ||
  fail "release workflow does not track the first-patch state"
[[ "$RELEASE_WORKFLOW" == *"[ \"\$TYPE\" == \"patch\" ] && [ \"\$ALREADY_RELEASED\" == \"true\" ] &&"* ]] ||
  fail "release workflow does not distinguish the tagged first-patch base"
[[ "$RELEASE_WORKFLOW" == *"[ \"\$PATCH\" -eq 0 ]"* ]] ||
  fail "release workflow accepts an already-tagged nonzero patch as the first patch"
[[ "$RELEASE_WORKFLOW" == *"RELEASE_VERSION=\"\$MAJOR.\$MINOR.\$((PATCH + 1))\""* ]] ||
  fail "release workflow does not increment an already-tagged patch version"
[[ "$RELEASE_WORKFLOW" == *"RELEASE_VERSION=\"\$BASE\""* ]] ||
  fail "release workflow does not preserve an untagged patch development version"
pass

# Exercise the completion gate with a deterministic gh stub. These scenarios
# prove that success requires the exact approval, selected checks, and an
# observed merge, while stale heads and failed checks fail closed.
WAITER_BIN="$TEMP_DIR/waiter-bin"
mkdir "$WAITER_BIN"
cat > "$WAITER_BIN/gh" <<'GH'
#!/usr/bin/env bash
set -euo pipefail
EXPECTED=$(printf 'a%.0s' {1..40})
if [ "$1" = "api" ] && [[ "$*" == *"/reviews?"* ]]; then
  echo approval >> "$WAITER_ORDER"
  if [ "$WAITER_SCENARIO" = "stale-approval" ]; then
    printf '[[{"user":{"login":"dd-octo-sts[bot]"},"state":"APPROVED","commit_id":"%s"}]]\n' \
      "$(printf 'b%.0s' {1..40})"
  else
    printf '[[{"user":{"login":"dd-octo-sts[bot]"},"state":"APPROVED","commit_id":"%s"}]]\n' \
      "$EXPECTED"
  fi
elif [ "$1" = "api" ]; then
  case "$WAITER_SCENARIO" in
    head-change)
      printf '{"head":{"sha":"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"},"state":"open","merged_at":null}\n'
      ;;
    closed)
      printf '{"head":{"sha":"%s"},"state":"closed","merged_at":null}\n' "$EXPECTED"
      ;;
    already-merged)
      printf '{"head":{"sha":"%s"},"state":"closed","merged_at":"2026-08-02T00:00:00Z"}\n' "$EXPECTED"
      ;;
    *)
      if [ -f "$WAITER_MERGED" ]; then
        printf '{"head":{"sha":"%s"},"state":"closed","merged_at":"2026-08-02T00:00:00Z"}\n' "$EXPECTED"
      else
        printf '{"head":{"sha":"%s"},"state":"open","merged_at":null}\n' "$EXPECTED"
      fi
      ;;
  esac
elif [ "$1 $2" = "pr checks" ]; then
  echo checks >> "$WAITER_ORDER"
  case "$WAITER_SCENARIO" in
    failed-check) printf '[{"name":"release-bump-ci","state":"FAILURE"}]\n' ;;
    missing-check) printf '[]\n' ;;
    pending-check) printf '[{"name":"release-bump-ci","state":"IN_PROGRESS"}]\n' ;;
    *) printf '[{"name":"release-bump-ci","state":"SUCCESS"}]\n' ;;
  esac
elif [ "$1 $2 $3" = "pr merge 698" ]; then
  [[ "$*" == *"--squash --match-head-commit $EXPECTED"* ]] || exit 98
  echo merge >> "$WAITER_ORDER"
  touch "$WAITER_MERGED"
else
  echo "unsupported waiter gh call: $*" >&2
  exit 99
fi
GH
chmod +x "$WAITER_BIN/gh"
WAITER_SHA=$(printf 'a%.0s' {1..40})

run_waiter() {
  local scenario=$1
  rm -f "$TEMP_DIR/waiter-merged" "$TEMP_DIR/waiter-order"
  WAITER_SCENARIO="$scenario" WAITER_MERGED="$TEMP_DIR/waiter-merged" \
    WAITER_ORDER="$TEMP_DIR/waiter-order" \
    RELEASE_BUMP_POLL_ATTEMPTS=1 RELEASE_BUMP_POLL_SECONDS=0 \
    PATH="$WAITER_BIN:$PATH" "$WAITER" \
      --repo DataDog/java-profiler --pr-number 698 \
      --expected-head-sha "$WAITER_SHA" \
      --check release-bump-ci >/dev/null
}

run_waiter success || fail "waiter rejected exact approval/check/merge success"
[ "$(<"$TEMP_DIR/waiter-order")" = $'approval\nchecks\nmerge' ] ||
  fail "waiter did not enforce approval, checks, then merge ordering"
pass
if run_waiter already-merged 2>/dev/null; then
  fail "waiter accepted a PR merged before its gates"
fi
pass
if run_waiter stale-approval 2>/dev/null; then
  fail "waiter accepted a stale approval"
fi
pass
if run_waiter head-change 2>/dev/null; then
  fail "waiter accepted a changed head"
fi
pass
if run_waiter failed-check 2>/dev/null; then
  fail "waiter accepted a failed selected check"
fi
pass
if run_waiter missing-check 2>/dev/null; then
  fail "waiter accepted a missing selected check"
fi
pass
if run_waiter pending-check 2>/dev/null; then
  fail "waiter accepted a pending selected check"
fi
pass
if run_waiter closed 2>/dev/null; then
  fail "waiter accepted a PR closed without merging"
fi
pass

# Run the release script against a filesystem-backed bare remote. The gh and
# validator stubs enforce the command contract without network access.
REMOTE="$TEMP_DIR/remote.git"
WORK="$TEMP_DIR/work"
FAKE_BIN="$TEMP_DIR/bin"
mkdir "$FAKE_BIN"
git init --bare --quiet "$REMOTE"
git --git-dir="$REMOTE" config core.hooksPath /dev/null
git init --quiet -b main "$WORK"
mkdir -p "$WORK/.github/scripts"
cp "$ROOT/.github/scripts/release.sh" "$WORK/.github/scripts/release.sh"
cat > "$WORK/.github/scripts/validate-release-bump.sh" <<'VALIDATOR'
#!/usr/bin/env bash
set -euo pipefail
echo "$*" >> "$VALIDATOR_CALLS"
if git --git-dir="$VALIDATOR_REMOTE" show-ref --tags --quiet; then
  echo "release tag was published before bump validation" >&2
  exit 1
fi
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
if [ "$1 $2 $3" = "api --method POST" ] && [[ "$4" == */pulls ]]; then
  [ "$GH_TOKEN" = "actions-token" ] || exit 98
  git --git-dir="$VALIDATOR_REMOTE" rev-parse refs/heads/automated/bump-1-49-0 > "$INITIAL_PR_HEAD"
  printf '{"number":698,"html_url":"https://example.invalid/pull/698"}\n'
elif [ "$1 $2 $3" = "api --method POST" ] && [[ "$4" == */issues/698/labels ]]; then
  [ "$GH_TOKEN" = "label-token" ] || exit 98
  printf '[]\n'
else
  echo "unsupported fake gh call: $*" >&2
  exit 99
fi
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
    INITIAL_PR_HEAD="$TEMP_DIR/initial-pr-head" \
    VALIDATOR_CALLS="$TEMP_DIR/validator-calls" VALIDATOR_REMOTE="$REMOTE" \
    GITHUB_REPOSITORY=DataDog/java-profiler GITHUB_TOKEN=actions-token \
    BUMP_LABEL_TOKEN=label-token \
    PATH="$FAKE_BIN:$PATH" \
    ./.github/scripts/release.sh MINOR
) >"$TEMP_DIR/release.log" 2>&1 || {
    tail -20 "$TEMP_DIR/release.log" >&2
    fail "release script failed against the local bare remote"
  }
BUMP_SHA=$(git --git-dir="$REMOTE" rev-parse refs/heads/automated/bump-1-49-0)
INITIAL_PR_SHA=$(<"$TEMP_DIR/initial-pr-head")
[ "$INITIAL_PR_SHA" != "$BUMP_SHA" ] ||
  fail "PR creation was not followed by a synchronize-producing commit update"
[ "$(git --git-dir="$REMOTE" rev-parse "$INITIAL_PR_SHA^")" = "$SOURCE_SHA" ] ||
  fail "initial PR commit parent differs from the release source"
[ "$(git --git-dir="$REMOTE" rev-parse "$INITIAL_PR_SHA^{tree}")" = \
  "$(git --git-dir="$REMOTE" rev-parse "$BUMP_SHA^{tree}")" ] ||
  fail "temporary and canonical bump commits do not have identical trees"
grep -Fq "api --method POST repos/DataDog/java-profiler/pulls" "$TEMP_DIR/gh-calls" ||
  fail "release script did not create the PR"
grep -Fq "api --method POST repos/DataDog/java-profiler/issues/698/labels" "$TEMP_DIR/gh-calls" ||
  fail "release script did not label the PR"
if grep -Fq "pr merge" "$TEMP_DIR/gh-calls"; then
  fail "release script merged before the external approval and CI gates"
fi
grep -Fq -- "--branch" "$TEMP_DIR/validator-calls" ||
  fail "release script did not validate the pushed bump branch"
grep -Fq -- "--base main" "$TEMP_DIR/validator-calls" ||
  fail "release script did not validate the bump base"
grep -Fq -- "--head automated/bump-1-49-0" "$TEMP_DIR/validator-calls" ||
  fail "release script did not validate the bump head"
grep -Fq -- "--expected-head-sha $BUMP_SHA" "$TEMP_DIR/validator-calls" ||
  fail "branch validation did not pin the bump SHA"
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
grep -Fqx "bump_pr_number=698" "$TEMP_DIR/release-outputs" ||
  fail "release outputs omitted bump PR number"
pass

# Verify that the first patch advances the initially tagged X.Y.0 release
# branch to X.Y.1, tags that release commit, and proposes X.Y.2-SNAPSHOT.
PATCH_REMOTE="$TEMP_DIR/patch-remote.git"
PATCH_WORK="$TEMP_DIR/patch-work"
PATCH_BIN="$TEMP_DIR/patch-bin"
mkdir "$PATCH_BIN"
git init --bare --quiet "$PATCH_REMOTE"
git --git-dir="$PATCH_REMOTE" config core.hooksPath /dev/null
git init --quiet -b 'release/1.48._' "$PATCH_WORK"
mkdir -p "$PATCH_WORK/.github/scripts"
cp "$ROOT/.github/scripts/release.sh" "$PATCH_WORK/.github/scripts/release.sh"
cat > "$PATCH_WORK/.github/scripts/validate-release-bump.sh" <<'VALIDATOR'
#!/usr/bin/env bash
set -euo pipefail
echo "$*" >> "$VALIDATOR_CALLS"
if git --git-dir="$VALIDATOR_REMOTE" show-ref --verify --quiet refs/tags/v_1.48.1; then
  echo "first patch tag was published before bump validation" >&2
  exit 1
fi
VALIDATOR
chmod +x "$PATCH_WORK/.github/scripts/validate-release-bump.sh"
printf 'version = "1.48.0-SNAPSHOT"\n' > "$PATCH_WORK/build.gradle.kts"
cp "$WORK/gradlew" "$PATCH_WORK/gradlew"
chmod +x "$PATCH_WORK/gradlew" "$PATCH_WORK/.github/scripts/release.sh"
cat > "$PATCH_BIN/gh" <<'GH'
#!/usr/bin/env bash
set -euo pipefail
echo "$*" >> "$GH_CALLS"
if [ "$1 $2 $3" = "api --method POST" ] && [[ "$4" == */pulls ]]; then
  [ "$GH_TOKEN" = "actions-token" ] || exit 98
  git --git-dir="$VALIDATOR_REMOTE" rev-parse refs/heads/automated/bump-1-48-2 > "$INITIAL_PR_HEAD"
  printf '{"number":700,"html_url":"https://example.invalid/pull/700"}\n'
elif [ "$1 $2 $3" = "api --method POST" ] && [[ "$4" == */issues/700/labels ]]; then
  [ "$GH_TOKEN" = "label-token" ] || exit 98
  printf '[]\n'
else
  echo "unsupported first-patch gh call: $*" >&2
  exit 99
fi
GH
chmod +x "$PATCH_BIN/gh"
git -C "$PATCH_WORK" config user.name "Release Test"
git -C "$PATCH_WORK" config user.email "release-test@example.invalid"
git -C "$PATCH_WORK" config commit.gpgsign false
git -C "$PATCH_WORK" config tag.gpgsign false
git -C "$PATCH_WORK" config core.hooksPath /dev/null
git -C "$PATCH_WORK" add .
git -C "$PATCH_WORK" commit --quiet -m initial
PATCH_SOURCE_SHA=$(git -C "$PATCH_WORK" rev-parse HEAD)
git -C "$PATCH_WORK" tag -a v_1.48.0 -m 'Release v_1.48.0 (minor) from main'
git -C "$PATCH_WORK" remote add origin "$PATCH_REMOTE"
git -C "$PATCH_WORK" push --quiet -u origin 'release/1.48._'
git -C "$PATCH_WORK" push --quiet origin v_1.48.0
(
  cd "$PATCH_WORK"
  GITHUB_OUTPUT="$TEMP_DIR/patch-outputs" GH_CALLS="$TEMP_DIR/patch-gh-calls" \
    INITIAL_PR_HEAD="$TEMP_DIR/patch-initial-pr-head" \
    VALIDATOR_CALLS="$TEMP_DIR/patch-validator-calls" VALIDATOR_REMOTE="$PATCH_REMOTE" \
    GITHUB_REPOSITORY=DataDog/java-profiler GITHUB_TOKEN=actions-token \
    BUMP_LABEL_TOKEN=label-token \
    PATH="$PATCH_BIN:$PATH" \
    ./.github/scripts/release.sh PATCH
) >"$TEMP_DIR/patch-release.log" 2>&1 || {
    tail -20 "$TEMP_DIR/patch-release.log" >&2
    fail "first patch release script failed against the local bare remote"
  }
PATCH_RELEASE_SHA=$(git --git-dir="$PATCH_REMOTE" rev-parse 'refs/heads/release/1.48._')
PATCH_BUMP_SHA=$(git --git-dir="$PATCH_REMOTE" rev-parse refs/heads/automated/bump-1-48-2)
[ "$(git --git-dir="$PATCH_REMOTE" show "$PATCH_RELEASE_SHA:build.gradle.kts")" = \
  'version = "1.48.1-SNAPSHOT"' ] ||
  fail "first patch release branch does not contain 1.48.1"
[ "$(git --git-dir="$PATCH_REMOTE" rev-parse 'refs/tags/v_1.48.1^{commit}')" = \
  "$PATCH_RELEASE_SHA" ] || fail "first patch tag does not identify the release commit"
[ "$(git --git-dir="$PATCH_REMOTE" rev-parse "$PATCH_RELEASE_SHA^")" = "$PATCH_SOURCE_SHA" ] ||
  fail "first patch release commit parent differs from the selected source"
[ "$(git --git-dir="$PATCH_REMOTE" show "$PATCH_BUMP_SHA:build.gradle.kts")" = \
  'version = "1.48.2-SNAPSHOT"' ] ||
  fail "first patch bump does not contain 1.48.2-SNAPSHOT"
[ "$(git --git-dir="$PATCH_REMOTE" rev-parse "$PATCH_BUMP_SHA^")" = "$PATCH_RELEASE_SHA" ] ||
  fail "first patch bump parent is not the release commit"
grep -Fq -- "--first-patch" "$TEMP_DIR/patch-validator-calls" ||
  fail "first patch preflight did not select first-patch validation"
grep -Fq -- "--source-sha $PATCH_SOURCE_SHA" "$TEMP_DIR/patch-validator-calls" ||
  fail "first patch preflight did not preserve the selected source SHA"
grep -Fq -- "--local-release-tag v_1.48.1" "$TEMP_DIR/patch-validator-calls" ||
  fail "first patch preflight did not validate the new annotated tag"
grep -Fqx "release_version=1.48.1" "$TEMP_DIR/patch-outputs" ||
  fail "first patch outputs omitted the release version"
grep -Fqx "next_version=1.48.2" "$TEMP_DIR/patch-outputs" ||
  fail "first patch outputs omitted the next development version"
pass

STUCK_PATCH_WORK="$TEMP_DIR/stuck-patch-work"
git clone --quiet --branch 'release/1.48._' "$PATCH_REMOTE" "$STUCK_PATCH_WORK"
if (
  cd "$STUCK_PATCH_WORK"
  PATH="$NETWORK_GUARD_BIN:$PATH" ./.github/scripts/release.sh PATCH
) >"$TEMP_DIR/stuck-patch.log" 2>&1; then
  fail "release script accepted an already-tagged nonzero patch version"
fi
grep -Fq 'is stuck at version 1.48.1' "$TEMP_DIR/stuck-patch.log" ||
  fail "release script did not preserve the stuck post-patch bump guard"
pass

# Verify major releases keep their generated release commit off protected main.
# The bump moves main directly from the recorded source to the next development
# series, while the release branch and annotated tag identify the 2.0.0 commit.
MAJOR_REMOTE="$TEMP_DIR/major-remote.git"
MAJOR_WORK="$TEMP_DIR/major-work"
MAJOR_BIN="$TEMP_DIR/major-bin"
mkdir "$MAJOR_BIN"
git init --bare --quiet "$MAJOR_REMOTE"
git --git-dir="$MAJOR_REMOTE" config core.hooksPath /dev/null
git init --quiet -b main "$MAJOR_WORK"
mkdir -p "$MAJOR_WORK/.github/scripts"
cp "$ROOT/.github/scripts/release.sh" "$MAJOR_WORK/.github/scripts/release.sh"
cp "$WORK/.github/scripts/validate-release-bump.sh" "$MAJOR_WORK/.github/scripts/validate-release-bump.sh"
printf 'version = "1.48.0-SNAPSHOT"\n' > "$MAJOR_WORK/build.gradle.kts"
cp "$WORK/gradlew" "$MAJOR_WORK/gradlew"
chmod +x "$MAJOR_WORK/.github/scripts/release.sh"
cat > "$MAJOR_BIN/gh" <<'GH'
#!/usr/bin/env bash
set -euo pipefail
echo "$*" >> "$GH_CALLS"
if [ "$1 $2 $3" = "api --method POST" ] && [[ "$4" == */pulls ]]; then
  [ "$GH_TOKEN" = "actions-token" ] || exit 98
  git --git-dir="$VALIDATOR_REMOTE" rev-parse refs/heads/automated/bump-2-1-0 > "$INITIAL_PR_HEAD"
  printf '{"number":699,"html_url":"https://example.invalid/pull/699"}\n'
elif [ "$1 $2 $3" = "api --method POST" ] && [[ "$4" == */issues/699/labels ]]; then
  [ "$GH_TOKEN" = "label-token" ] || exit 98
  printf '[]\n'
elif [ "$1 $2 $3" = "pr merge 699" ]; then
  [ "$GH_TOKEN" = "actions-token" ] || exit 98
  :
else
  echo "unsupported fake gh call: $*" >&2
  exit 99
fi
GH
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
    INITIAL_PR_HEAD="$TEMP_DIR/major-initial-pr-head" \
    VALIDATOR_CALLS="$TEMP_DIR/major-validator-calls" VALIDATOR_REMOTE="$MAJOR_REMOTE" \
    GITHUB_REPOSITORY=DataDog/java-profiler GITHUB_TOKEN=actions-token \
    BUMP_LABEL_TOKEN=label-token \
    PATH="$MAJOR_BIN:$PATH" \
    ./.github/scripts/release.sh MAJOR
) >"$TEMP_DIR/major-release.log" 2>&1 || {
    tail -20 "$TEMP_DIR/major-release.log" >&2
    fail "major release script failed against the local bare remote"
  }
MAJOR_MAIN_SHA=$(git --git-dir="$MAJOR_REMOTE" rev-parse refs/heads/main)
MAJOR_RELEASE_SHA=$(git --git-dir="$MAJOR_REMOTE" rev-parse refs/heads/release/2.0._)
MAJOR_BUMP_SHA=$(git --git-dir="$MAJOR_REMOTE" rev-parse refs/heads/automated/bump-2-1-0)
MAJOR_INITIAL_PR_SHA=$(<"$TEMP_DIR/major-initial-pr-head")
[ "$MAJOR_INITIAL_PR_SHA" != "$MAJOR_BUMP_SHA" ] ||
  fail "major bump did not produce a synchronize update"
[ "$MAJOR_MAIN_SHA" = "$MAJOR_INITIAL_SHA" ] ||
  fail "major release pushed its generated release commit to protected main"
[ "$(git --git-dir="$MAJOR_REMOTE" show "$MAJOR_RELEASE_SHA:build.gradle.kts")" = \
  'version = "2.0.0-SNAPSHOT"' ] ||
  fail "major release branch does not contain the release version"
[ "$(git --git-dir="$MAJOR_REMOTE" show "$MAJOR_BUMP_SHA:build.gradle.kts")" = \
  'version = "2.1.0-SNAPSHOT"' ] ||
  fail "major bump does not contain the next development version"
[ "$(git --git-dir="$MAJOR_REMOTE" rev-parse "$MAJOR_RELEASE_SHA^")" = "$MAJOR_INITIAL_SHA" ] ||
  fail "major release commit parent is not the recorded main source"
[ "$(git --git-dir="$MAJOR_REMOTE" rev-parse "$MAJOR_BUMP_SHA^")" = "$MAJOR_INITIAL_SHA" ] ||
  fail "major bump parent is not the recorded main source"
[ "$(git --git-dir="$MAJOR_REMOTE" rev-parse 'refs/tags/v_2.0.0^{commit}')" = "$MAJOR_RELEASE_SHA" ] ||
  fail "major release tag does not point to the release commit"
grep -Fqx "source_sha=$MAJOR_INITIAL_SHA" "$TEMP_DIR/major-outputs" ||
  fail "major release outputs changed the recorded main source SHA"
grep -Fq -- "--source-sha $MAJOR_INITIAL_SHA" "$TEMP_DIR/major-validator-calls" ||
  fail "major branch validation did not use the original main source"
grep -Fq -- "--expected-head-sha $MAJOR_BUMP_SHA" "$TEMP_DIR/major-validator-calls" ||
  fail "major branch validation did not pin the bump SHA"
grep -Fq -- "--local-release-tag v_2.0.0" "$TEMP_DIR/major-validator-calls" ||
  fail "major preflight did not validate the local annotated release tag"
if grep -Fq "pr merge" "$TEMP_DIR/major-gh-calls"; then
  fail "major release script merged before the external approval and CI gates"
fi
pass

echo "PASS: $TESTS hermetic release-automation test groups"
