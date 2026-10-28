#!/usr/bin/env bash

set -euo pipefail

# Copyright 2026, Datadog, Inc

# Hermetic tests for the tag-based release automation.
# Run with: .github/scripts/tests/test_release_automation.sh

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)
RELEASE_SCRIPT="$ROOT/.github/scripts/release.sh"
TRIVIAL_VALIDATOR="$ROOT/.github/scripts/validate-trivial-approval.sh"
COMPUTE_VERSION="$ROOT/utils/compute-version.sh"
TEMP_DIR=$(mktemp -d)
TESTS=0

# This suite must never mutate GitHub or any other network remote. Restrict Git
# to filesystem transports and shadow every network-capable command.
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

# --- Trivial approval authorization tests (kept from old suite) -------------

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

# --- Script content assertions ----------------------------------------------

RELEASE_SCRIPT_CONTENT=$(<"$RELEASE_SCRIPT")
[[ "$RELEASE_SCRIPT_CONTENT" != *"set -x"* ]] ||
  fail "release script enables credential-bearing shell tracing"
[[ "$RELEASE_SCRIPT_CONTENT" != *"gh pr merge"* ]] ||
  fail "release script can merge PRs"
[[ "$RELEASE_SCRIPT_CONTENT" != *"incrementVersion"* ]] ||
  fail "release script uses incrementVersion"
[[ "$RELEASE_SCRIPT_CONTENT" != *"printVersion"* ]] ||
  fail "release script uses printVersion"
[[ "$RELEASE_SCRIPT_CONTENT" != *"BUMP_LABEL_TOKEN"* ]] ||
  fail "release script uses BUMP_LABEL_TOKEN"
[[ "$RELEASE_SCRIPT_CONTENT" != *"validate-release-bump"* ]] ||
  fail "release script references validate-release-bump"
[[ "$RELEASE_SCRIPT_CONTENT" != *"wait-release-bump"* ]] ||
  fail "release script references wait-release-bump"
pass

[ ! -e "$ROOT/utils/finalize-release-bump.sh" ] ||
  fail "obsolete human release-bump finalizer still exists"
[ ! -e "$ROOT/.github/scripts/validate-release-bump.sh" ] ||
  fail "obsolete validate-release-bump.sh still exists"
[ ! -e "$ROOT/.github/scripts/wait-release-bump.sh" ] ||
  fail "obsolete wait-release-bump.sh still exists"
[ ! -e "$ROOT/.github/chainguard/self.release-bump.label-pr.sts.yaml" ] ||
  fail "obsolete release-bump label STS policy still exists"
pass

APPROVAL_WORKFLOW=$(<"$ROOT/.github/workflows/approve-trivial.yml")
[[ "$APPROVAL_WORKFLOW" != *"release_bump"* ]] ||
  fail "approval workflow still classifies release bumps"
[[ "$APPROVAL_WORKFLOW" != *"validate-release-bump"* ]] ||
  fail "approval workflow still validates release bumps"
[[ "$APPROVAL_WORKFLOW" == *"github.event.label.name == 'trivial'"* ]] ||
  fail "approval workflow does not trigger on trivial"
[[ "$APPROVAL_WORKFLOW" == *"github.event.sender.login"* ]] ||
  fail "approval workflow does not use the label event sender"
[[ "$APPROVAL_WORKFLOW" == *"commit_id: process.env.EXPECTED_HEAD_SHA"* ]] ||
  fail "approval is not pinned to the validated SHA"
pass

CI_WORKFLOW=$(<"$ROOT/.github/workflows/ci.yml")
[[ "$CI_WORKFLOW" != *"release-bump-ci"* ]] ||
  fail "CI workflow still has release-bump-ci job"
[[ "$CI_WORKFLOW" != *"validate-release-bump"* ]] ||
  fail "CI workflow still references validate-release-bump"
pass

RELEASE_WORKFLOW=$(<"$ROOT/.github/workflows/release-validated.yml")
[[ "$RELEASE_WORKFLOW" != *"printVersion"* ]] ||
  fail "release workflow still uses printVersion"
[[ "$RELEASE_WORKFLOW" != *"wait-release-bump"* ]] ||
  fail "release workflow still references wait-release-bump"
[[ "$RELEASE_WORKFLOW" != *"bump_pr_number"* ]] ||
  fail "release workflow still has bump_pr_number output"
[[ "$RELEASE_WORKFLOW" != *"bump_branch"* ]] ||
  fail "release workflow still has bump_branch output"
[[ "$RELEASE_WORKFLOW" == *"compute-version.sh"* ]] ||
  fail "release workflow does not use compute-version.sh"
pass

# --- Release script integration tests (hermetic, local bare remote) ----------

setup_remote() {
  local remote="$TEMP_DIR/remote-$RANDOM.git"
  git init --bare --quiet "$remote"
  git --git-dir="$remote" config core.hooksPath /dev/null
  echo "$remote"
}

setup_work() {
  local remote=$1
  local branch=$2
  local work="$TEMP_DIR/work-$RANDOM"
  git init --quiet -b "$branch" "$work"
  git -C "$work" config user.name "Release Test"
  git -C "$work" config user.email "release-test@example.invalid"
  git -C "$work" config commit.gpgsign false
  git -C "$work" config tag.gpgsign false
  git -C "$work" config core.hooksPath /dev/null
  mkdir -p "$work/.github/scripts" "$work/utils"
  cp "$RELEASE_SCRIPT" "$work/.github/scripts/release.sh"
  cp "$COMPUTE_VERSION" "$work/utils/compute-version.sh"
  chmod +x "$work/.github/scripts/release.sh" "$work/utils/compute-version.sh"
  echo "initial" > "$work/file.txt"
  git -C "$work" add .
  git -C "$work" commit --quiet -m "initial"
  git -C "$work" remote add origin "$remote"
  git -C "$work" push --quiet -u origin "$branch"
  echo "$work"
}

# Test: Minor release from main
REMOTE=$(setup_remote)
WORK=$(setup_work "$REMOTE" main)
# Create a tag on main so compute-version.sh has a base
git -C "$WORK" tag -a "v_1.48.0" -m "Release v_1.48.0"
git -C "$WORK" push --quiet origin "v_1.48.0"
SOURCE_SHA=$(git -C "$WORK" rev-parse HEAD)
GITHUB_OUTPUT="$TEMP_DIR/minor-outputs" \
  PATH="$WORK/utils:$PATH" \
  bash -c 'cd "$0" && ./.github/scripts/release.sh MINOR --dry-run' "$WORK" >/dev/null 2>&1 || \
  fail "minor release dry-run failed"
# Now do the real release
GITHUB_OUTPUT="$TEMP_DIR/minor-outputs" \
  PATH="$WORK/utils:$PATH" \
  bash -c 'cd "$0" && ./.github/scripts/release.sh MINOR' "$WORK" >/dev/null 2>&1 || \
  fail "minor release failed"
git --git-dir="$REMOTE" show-ref --verify --quiet "refs/tags/v_1.49.0" ||
  fail "minor release tag was not pushed"
git --git-dir="$REMOTE" show-ref --verify --quiet "refs/heads/release/1.49._" ||
  fail "minor release branch was not pushed"
[ "$(git --git-dir="$REMOTE" rev-parse 'refs/tags/v_1.49.0^{commit}')" = "$SOURCE_SHA" ] ||
  fail "minor release tag does not point to source SHA"
grep -Fqx "release_version=1.49.0" "$TEMP_DIR/minor-outputs" ||
  fail "minor release outputs omitted release version"
grep -Fqx "release_branch=release/1.49._" "$TEMP_DIR/minor-outputs" ||
  fail "minor release outputs omitted release branch"
pass

# Test: Major release from main
REMOTE=$(setup_remote)
WORK=$(setup_work "$REMOTE" main)
git -C "$WORK" tag -a "v_1.49.0" -m "Release v_1.49.0"
git -C "$WORK" push --quiet origin "v_1.49.0"
SOURCE_SHA=$(git -C "$WORK" rev-parse HEAD)
GITHUB_OUTPUT="$TEMP_DIR/major-outputs" \
  PATH="$WORK/utils:$PATH" \
  bash -c 'cd "$0" && ./.github/scripts/release.sh MAJOR' "$WORK" >/dev/null 2>&1 || \
  fail "major release failed"
git --git-dir="$REMOTE" show-ref --verify --quiet "refs/tags/v_2.0.0" ||
  fail "major release tag was not pushed"
git --git-dir="$REMOTE" show-ref --verify --quiet "refs/heads/release/2.0._" ||
  fail "major release branch was not pushed"
[ "$(git --git-dir="$REMOTE" rev-parse 'refs/tags/v_2.0.0^{commit}')" = "$SOURCE_SHA" ] ||
  fail "major release tag does not point to source SHA"
grep -Fqx "release_version=2.0.0" "$TEMP_DIR/major-outputs" ||
  fail "major release outputs omitted release version"
pass

# Test: Patch release from release branch
REMOTE=$(setup_remote)
WORK=$(setup_work "$REMOTE" "release/1.48._")
git -C "$WORK" tag -a "v_1.48.2" -m "Release v_1.48.2"
git -C "$WORK" push --quiet origin "v_1.48.2"
SOURCE_SHA=$(git -C "$WORK" rev-parse HEAD)
GITHUB_OUTPUT="$TEMP_DIR/patch-outputs" \
  PATH="$WORK/utils:$PATH" \
  bash -c 'cd "$0" && ./.github/scripts/release.sh PATCH' "$WORK" >/dev/null 2>&1 || \
  fail "patch release failed"
git --git-dir="$REMOTE" show-ref --verify --quiet "refs/tags/v_1.48.3" ||
  fail "patch release tag was not pushed"
# Patch should NOT create a new branch
if git --git-dir="$REMOTE" show-ref --verify --quiet "refs/heads/release/1.48.3._" 2>/dev/null; then
  fail "patch release should not create a new branch"
fi
[ "$(git --git-dir="$REMOTE" rev-parse 'refs/tags/v_1.48.3^{commit}')" = "$SOURCE_SHA" ] ||
  fail "patch release tag does not point to source SHA"
grep -Fqx "release_version=1.48.3" "$TEMP_DIR/patch-outputs" ||
  fail "patch release outputs omitted release version"
pass

# Test: First patch on new release branch
REMOTE=$(setup_remote)
WORK=$(setup_work "$REMOTE" "release/1.50._")
git -C "$WORK" tag -a "v_1.50.0" -m "Release v_1.50.0"
git -C "$WORK" push --quiet origin "v_1.50.0"
GITHUB_OUTPUT="$TEMP_DIR/first-patch-outputs" \
  PATH="$WORK/utils:$PATH" \
  bash -c 'cd "$0" && ./.github/scripts/release.sh PATCH' "$WORK" >/dev/null 2>&1 || \
  fail "first patch release failed"
git --git-dir="$REMOTE" show-ref --verify --quiet "refs/tags/v_1.50.1" ||
  fail "first patch tag was not pushed"
pass

# Test: Tag already exists → fail
REMOTE=$(setup_remote)
WORK=$(setup_work "$REMOTE" main)
git -C "$WORK" tag -a "v_1.48.0" -m "Release v_1.48.0"
git -C "$WORK" push --quiet origin "v_1.48.0"
# Compute what the minor release would produce
COLLISION_VERSION=$(cd "$WORK" && PATH="$WORK/utils:$PATH" utils/compute-version.sh --release --minor)
# Create the collision tag on a DIFFERENT commit so it doesn't affect computation
git -C "$WORK" checkout --quiet HEAD~0  # stay on HEAD but create a dummy commit for the tag
# Actually, just create the tag pointing to a new dummy commit
git -C "$WORK" checkout -b collision-branch --quiet
echo "collision" > "$WORK/collision.txt"
git -C "$WORK" add collision.txt
git -C "$WORK" commit --quiet -m "collision base"
git -C "$WORK" tag -a "v_${COLLISION_VERSION}" -m "Pre-existing collision"
git -C "$WORK" push --quiet origin "v_${COLLISION_VERSION}"
git -C "$WORK" checkout --quiet main
# Now v_${COLLISION_VERSION} exists but is NOT reachable from main HEAD
# The release script should still detect it via git rev-parse
if bash -c 'cd "$0" && PATH="$1" ./.github/scripts/release.sh MINOR' "$WORK" "$WORK/utils:$PATH" >/dev/null 2>&1; then
  fail "release script accepted an already-existing tag"
fi
pass

# Test: Patch from main → fail
REMOTE=$(setup_remote)
WORK=$(setup_work "$REMOTE" main)
git -C "$WORK" tag -a "v_1.48.0" -m "Release v_1.48.0"
if bash -c 'cd "$0" && PATH="$1" ./.github/scripts/release.sh PATCH' "$WORK" "$WORK/utils:$PATH" >/dev/null 2>&1; then
  fail "release script accepted patch from main"
fi
pass

# Test: Minor from release branch → fail
REMOTE=$(setup_remote)
WORK=$(setup_work "$REMOTE" "release/1.48._")
git -C "$WORK" tag -a "v_1.48.0" -m "Release v_1.48.0"
if bash -c 'cd "$0" && PATH="$1" ./.github/scripts/release.sh MINOR' "$WORK" "$WORK/utils:$PATH" >/dev/null 2>&1; then
  fail "release script accepted minor from release branch"
fi
pass

# Test: Version computation after release
REMOTE=$(setup_remote)
WORK=$(setup_work "$REMOTE" main)
git -C "$WORK" tag -a "v_1.48.0" -m "Release v_1.48.0"
bash -c 'cd "$0" && PATH="$1" ./.github/scripts/release.sh MINOR' "$WORK" "$WORK/utils:$PATH" >/dev/null 2>&1
# After minor release, main should compute 1.50.0-SNAPSHOT
NEXT_VERSION=$(cd "$WORK" && PATH="$WORK/utils:$PATH" utils/compute-version.sh)
[ "$NEXT_VERSION" = "1.50.0-SNAPSHOT" ] ||
  fail "expected 1.50.0-SNAPSHOT after minor release, got '$NEXT_VERSION'"
pass

# Test: Dry-run does not push
REMOTE=$(setup_remote)
WORK=$(setup_work "$REMOTE" main)
git -C "$WORK" tag -a "v_1.48.0" -m "Release v_1.48.0"
bash -c 'cd "$0" && PATH="$1" ./.github/scripts/release.sh MINOR --dry-run' "$WORK" "$WORK/utils:$PATH" >/dev/null 2>&1
if git --git-dir="$REMOTE" show-ref --verify --quiet "refs/tags/v_1.49.0" 2>/dev/null; then
  fail "dry-run pushed a tag"
fi
pass

# --- Release CLI monitoring tests (GitHub CLI fixture, no network) ------------

REMOTE=$(setup_remote)
WORK=$(setup_work "$REMOTE" main)
CLI_SHA=$(git -C "$WORK" rev-parse HEAD)
CLI_BIN="$TEMP_DIR/cli-bin"
CLI_STATE="$TEMP_DIR/cli-state"
mkdir "$CLI_BIN" "$CLI_STATE"
cat > "$CLI_BIN/gh" <<'EOF'
#!/usr/bin/env bash
set -euo pipefail
printf '%s\n' "$*" >> "$CLI_STATE/calls"
case "$1 $2" in
  'auth status') echo 'Logged in to github.com account release-test' ;;
  'repo view')
    case "$4" in
      nameWithOwner) echo 'DataDog/java-profiler' ;;
      url) echo 'https://github.com/DataDog/java-profiler' ;;
      viewerPermission) echo WRITE ;;
      *) exit 97 ;;
    esac
    ;;
  'api user') echo release-test ;;
  'api repos/DataDog/java-profiler/actions/runs?event=workflow_dispatch&per_page=50')
    printf '%s\n' "$CLI_RUN_ID"
    ;;
  'workflow run') exit "$CLI_DISPATCH_EXIT" ;;
  'run watch')
    [ "$3" = 4242 ] && [ "$4 $5" = '--repo DataDog/java-profiler' ] || exit 97
    count=0
    [ ! -f "$CLI_STATE/watches" ] || count=$(cat "$CLI_STATE/watches")
    printf '%s\n' "$((count + 1))" > "$CLI_STATE/watches"
    if { [ "$count" -eq 0 ] && [ "${CLI_WATCH_HANG:-0}" -eq 1 ]; } ||
       { [ "$count" -gt 0 ] && [ "${CLI_NEXT_WATCH_HANG:-0}" -eq 1 ]; }; then
      echo "$$" > "$CLI_STATE/watch-pid"
      exec /bin/sleep 30
    fi
    if [ "$count" -eq 0 ]; then
      /bin/sleep "${CLI_WATCH_DELAY:-0}"
      exit "$CLI_WATCH_EXIT"
    fi
    exit "$CLI_NEXT_WATCH_EXIT"
    ;;
  'run view')
    [ "$3" = 4242 ] && [ "$4 $5" = '--repo DataDog/java-profiler' ] || exit 97
    if [ "${CLI_QUERY_HANG:-0}" -eq 1 ]; then
      echo "$$" > "$CLI_STATE/query-pid"
      exec /bin/sleep 30
    fi
    [ "$CLI_QUERY_EXIT" -eq 0 ] || exit "$CLI_QUERY_EXIT"
    printf '%s\n' "$CLI_REMOTE_JSON" | jq -r "${@: -1}"
    ;;
  *) echo "Unexpected fixture command: $*" >&2; exit 97 ;;
esac
EOF
cat > "$CLI_BIN/sleep" <<'EOF'
#!/usr/bin/env bash
# Keep deadline polling asynchronous while skipping discovery/reconnect delays.
if [ "$1" = 1 ]; then
  exec /bin/sleep 0.02
fi
exit 0
EOF
chmod +x "$CLI_BIN/gh" "$CLI_BIN/sleep"

expect_monitor() {
  local name=$1 expected_exit=$2 expected_status=$3 watches=$4 views=$5
  shift 5
  local actual_exit=0
  rm -f "$CLI_STATE/watches" "$CLI_STATE/"*-pid
  : > "$CLI_STATE/calls"
  CLI_OUTPUT=$(
    cd "$WORK"
    env PATH="$CLI_BIN:$PATH" CLI_STATE="$CLI_STATE" \
      RELEASE_MONITOR_TIMEOUT_SECONDS=3600 \
      CLI_RUN_ID=4242 CLI_DISPATCH_EXIT=0 CLI_WATCH_EXIT=0 CLI_NEXT_WATCH_EXIT=1 \
      CLI_QUERY_EXIT=0 CLI_REMOTE_JSON='{"status":"completed","conclusion":"success"}' \
      "$@" bash "$ROOT/utils/release.sh" minor --branch main --commit "$CLI_SHA" 2>&1
  ) || actual_exit=$?
  [ "$actual_exit" -eq "$expected_exit" ] ||
    fail "$name: expected exit $expected_exit, got $actual_exit"
  [[ "$CLI_OUTPUT" == *"Status: $expected_status"* ]] ||
    fail "$name: expected summary '$expected_status'"
  [ "$(awk '/^workflow run / { n++ } END { print n+0 }' "$CLI_STATE/calls")" -eq 1 ] ||
    fail "$name: workflow must be dispatched exactly once"
  [ "$(awk '/^run watch / { n++ } END { print n+0 }' "$CLI_STATE/calls")" -eq "$watches" ] ||
    fail "$name: unexpected watch count"
  [ "$(awk '/^run view / { n++ } END { print n+0 }' "$CLI_STATE/calls")" -eq "$views" ] ||
    fail "$name: unexpected status query count"
  for pid_file in "$CLI_STATE/"*-pid; do
    [ -f "$pid_file" ] || continue
    if kill -0 "$(cat "$pid_file")" 2>/dev/null; then
      fail "$name: timed-out CLI process is still running"
    fi
  done
  pass
}

expect_monitor 'watch succeeds' 0 'WORKFLOW SUCCEEDED' 1 0
expect_monitor 'connection lost after success' 0 'WORKFLOW SUCCEEDED' 1 1 CLI_WATCH_EXIT=1
for conclusion in failure startup_failure cancelled timed_out action_required stale neutral skipped; do
  expected_status='WORKFLOW COMPLETED'
  expected_message="Workflow completed with conclusion: $conclusion"
  case "$conclusion" in
    failure|startup_failure)
      expected_status='WORKFLOW FAILED'
      expected_message="Workflow failed! (conclusion: $conclusion)"
      ;;
  esac
  expect_monitor "confirmed $conclusion" 1 "$expected_status" 1 1 \
    CLI_WATCH_EXIT=1 CLI_REMOTE_JSON="{\"status\":\"completed\",\"conclusion\":\"$conclusion\"}"
  [[ "$CLI_OUTPUT" == *"$expected_message"* ]] ||
    fail "immediate result lost GitHub conclusion $conclusion"
  [[ "$CLI_OUTPUT" == *"Workflow conclusion: $conclusion"* ]] ||
    fail "terminal summary lost GitHub conclusion $conclusion"
  [[ "$CLI_OUTPUT" != *'Status: WORKFLOW STATUS UNKNOWN'* ]] ||
    fail "known conclusion $conclusion was reported as unknown"
  if [ "$expected_status" = 'WORKFLOW COMPLETED' ]; then
    [[ "$CLI_OUTPUT" != *'Status: WORKFLOW FAILED'* ]] ||
      fail "conclusion $conclusion was incorrectly reported as failure"
  fi
done
expect_monitor 'monitor reconnects to active run' 0 'WORKFLOW SUCCEEDED' 2 1 \
  CLI_WATCH_EXIT=1 CLI_NEXT_WATCH_EXIT=0 \
  CLI_REMOTE_JSON='{"status":"in_progress","conclusion":null}'
expect_monitor 'monitor cannot reconnect to active run' 1 'WORKFLOW STATUS UNKNOWN' 3 3 \
  CLI_WATCH_EXIT=1 CLI_REMOTE_JSON='{"status":"in_progress","conclusion":null}'
expect_monitor 'GitHub status unavailable' 1 'WORKFLOW STATUS UNKNOWN' 3 3 \
  CLI_WATCH_EXIT=1 CLI_QUERY_EXIT=1
[[ "$CLI_OUTPUT" != *'Status: WORKFLOW FAILED'* ]] ||
  fail 'unavailable GitHub status was reported as workflow failure'
expect_monitor 'completed run has no conclusion' 1 'WORKFLOW STATUS UNKNOWN' 3 3 \
  CLI_WATCH_EXIT=1 CLI_REMOTE_JSON='{"status":"completed","conclusion":null}'
expect_monitor 'completed run has an unrecognized conclusion' 1 'WORKFLOW STATUS UNKNOWN' 3 3 \
  CLI_WATCH_EXIT=1 CLI_REMOTE_JSON='{"status":"completed","conclusion":"future_value"}'
expect_monitor 'run discovery exhausted' 1 'WORKFLOW STATUS UNKNOWN' 0 0 CLI_RUN_ID=
[[ "$CLI_OUTPUT" != *'Status: DRY-RUN COMPLETED'* ]] ||
  fail 'unknown dry-run status was reported as completed'
expect_monitor 'dispatch fails' 1 'FAILED TO TRIGGER WORKFLOW' 0 0 CLI_DISPATCH_EXIT=1

expect_monitor 'watch deadline expires' 1 'WORKFLOW STATUS UNKNOWN' 1 1 \
  RELEASE_MONITOR_TIMEOUT_SECONDS=1 CLI_WATCH_HANG=1 \
  CLI_REMOTE_JSON='{"status":"in_progress","conclusion":null}'
[[ "$CLI_OUTPUT" == *'Monitoring timed out after 1 seconds'* ]] ||
  fail 'watch deadline did not report a monitoring timeout'
[[ "$CLI_OUTPUT" != *'Status: WORKFLOW FAILED'* ]] ||
  fail 'local deadline was reported as remote workflow failure'

expect_monitor 'final status confirms success after watch deadline' 0 'WORKFLOW SUCCEEDED' 1 1 \
  RELEASE_MONITOR_TIMEOUT_SECONDS=1 CLI_WATCH_HANG=1

expect_monitor 'status query deadline expires' 1 'WORKFLOW STATUS UNKNOWN' 1 1 \
  RELEASE_MONITOR_TIMEOUT_SECONDS=1 CLI_WATCH_EXIT=1 CLI_QUERY_HANG=1

expect_monitor 'final status query is also bounded' 1 'WORKFLOW STATUS UNKNOWN' 1 1 \
  RELEASE_MONITOR_TIMEOUT_SECONDS=1 CLI_WATCH_HANG=1 CLI_QUERY_HANG=1

monitor_started=$SECONDS
expect_monitor 'reconnections share the original deadline' 1 'WORKFLOW STATUS UNKNOWN' 2 2 \
  RELEASE_MONITOR_TIMEOUT_SECONDS=5 CLI_WATCH_EXIT=1 CLI_WATCH_DELAY=3 \
  CLI_NEXT_WATCH_HANG=1 CLI_REMOTE_JSON='{"status":"in_progress","conclusion":null}'
[ "$((SECONDS - monitor_started))" -lt 7 ] ||
  fail 'reconnecting reset the monitoring deadline'

for invalid_timeout in 0 -1 01 invalid 2147483648 999999999999999999999; do
  : > "$CLI_STATE/calls"
  if CLI_OUTPUT=$(
    cd "$WORK"
    env PATH="$CLI_BIN:$PATH" CLI_STATE="$CLI_STATE" \
      RELEASE_MONITOR_TIMEOUT_SECONDS="$invalid_timeout" \
      bash "$ROOT/utils/release.sh" minor --branch main --commit "$CLI_SHA" 2>&1
  ); then
    fail "invalid monitoring timeout '$invalid_timeout' was accepted"
  fi
  [[ "$CLI_OUTPUT" == *'RELEASE_MONITOR_TIMEOUT_SECONDS must be a positive integer'* ]] ||
    fail "invalid monitoring timeout '$invalid_timeout' did not report a validation error"
  [ "$(awk '/^workflow run / { n++ } END { print n+0 }' "$CLI_STATE/calls")" -eq 0 ] ||
    fail 'invalid monitoring timeout dispatched a workflow'
done
pass

echo "PASS: $TESTS hermetic release-automation test groups"
