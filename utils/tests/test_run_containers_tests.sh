#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

# Hermetic tests for the host-side clone, source mount probe and --pids-limit of
# utils/run-containers-tests.sh, with a fake podman/docker on PATH.
# Run with: bash utils/tests/test_run_containers_tests.sh

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
RUNNER="$SCRIPT_DIR/../run-containers-tests.sh"
TESTS=0
FAILED=0

TEMP_DIR=$(mktemp -d)
trap 'rm -rf "$TEMP_DIR"' EXIT
# Fixture commits and clones must not run the developer's global hooks or signing.
export GIT_CONFIG_GLOBAL=/dev/null GIT_CONFIG_NOSYSTEM=1
# The space checks that paths survive the script's eval-built container command.
FIXTURE="$TEMP_DIR/fixture root"
BIN="$TEMP_DIR/bin"
mkdir -p "$FIXTURE" "$BIN"

pass() {
  TESTS=$((TESTS + 1))
}

fail() {
  TESTS=$((TESTS + 1))
  FAILED=$((FAILED + 1))
  echo "FAIL: $*" >&2
}

check() {
  local description=$1
  shift
  if "$@"; then
    pass
  else
    fail "$description"
  fi
}

# --- Fake container runtime --------------------------------------------------------------
# Appends key=value lines to $FAKE_STATE (image=, probe_*=, run_*=, source_*=).
# FAKE_PROBE=ok|statfs|empty, FAKE_RUN_EXIT and FAKE_RUN_SIGNAL=TERM steer the outcome.
cat > "$BIN/podman" <<'EOF'
#!/usr/bin/env bash
case "$1" in
  image) echo "image=$2" >> "$FAKE_STATE"; exit 0 ;;
  run) shift ;;
  *) echo "fake runtime: unexpected command $1" >> "$FAKE_STATE"; exit 99 ;;
esac
args=("$@")
vol=""
for ((i = 0; i < ${#args[@]}; i++)); do
  if [[ "${args[$i]}" == "-v" ]]; then
    vol=${args[$((i + 1))]}
  fi
done
host=${vol%%:/*}
n=${#args[@]}
# The emulated container side must not see a global git config set by a test.
export GIT_CONFIG_GLOBAL=/dev/null
if [[ $n -ge 3 && "${args[$((n - 3))]}" == "test" ]]; then
  marker=${args[$((n - 1))]#/probe/}
  echo "probe_vol=$vol" >> "$FAKE_STATE"
  echo "probe_marker=$marker" >> "$FAKE_STATE"
  case "${FAKE_PROBE:-ok}" in
    statfs) echo "Error: statfs $host: no such file or directory" >&2; exit 125 ;;
    empty) exit 1 ;;
    *) test -e "$host/$marker" ;;
  esac
  exit
fi
echo "run_vol=$vol" >> "$FAKE_STATE"
echo "run_argv=$*" >> "$FAKE_STATE"
if [[ "$vol" == *:/source* ]]; then
  echo "source_host=$host" >> "$FAKE_STATE"
  if [[ -d "$host/.git" ]]; then
    echo "source_gitdir=dir" >> "$FAKE_STATE"
  else
    echo "source_gitdir=other" >> "$FAKE_STATE"
  fi
  echo "source_head=$(git -C "$host" rev-parse HEAD 2>/dev/null)" >> "$FAKE_STATE"
  echo "source_mode=$(ls -ld "$host" | cut -c1-10)" >> "$FAKE_STATE"
  echo "source_head_file_mode=$(ls -l "$host/.git/HEAD" | cut -c1-10)" >> "$FAKE_STATE"
  echo "source_ref_format=$(git -C "$host" rev-parse --show-ref-format 2>/dev/null)" >> "$FAKE_STATE"
  clone_dir=$(mktemp -d "$FAKE_WORK/clone.XXXXXX")
  if git clone --quiet --depth 1 "file://$host" "$clone_dir/ws" 2>/dev/null; then
    echo "source_clonable=yes" >> "$FAKE_STATE"
  else
    echo "source_clonable=no" >> "$FAKE_STATE"
  fi
fi
if [[ "${FAKE_RUN_SIGNAL:-}" == "TERM" ]]; then
  kill -TERM "$PPID"
fi
exit "${FAKE_RUN_EXIT:-0}"
EOF
chmod +x "$BIN/podman"
cp "$BIN/podman" "$BIN/docker"

# --- Fixture repositories ----------------------------------------------------------------
populate_project() {
  local dir=$1
  mkdir -p "$dir/utils" "$dir/gradle/wrapper"
  cp "$RUNNER" "$dir/utils/run-containers-tests.sh"
  printf '#!/bin/sh\nexit 0\n' > "$dir/gradlew"
  chmod +x "$dir/gradlew"
  echo "distributionUrl=unused" > "$dir/gradle/wrapper/gradle-wrapper.properties"
}

git_quiet() {
  git -c user.name=Test -c user.email=test@test.invalid -c commit.gpgsign=false \
    -c init.defaultBranch=main "$@" >/dev/null 2>&1
}

MAIN="$FIXTURE/main"
WORKTREE="$FIXTURE/worktree"
NOGIT="$FIXTURE/nogit"
populate_project "$MAIN"
git_quiet init "$MAIN"
git_quiet -C "$MAIN" add -A
git_quiet -C "$MAIN" commit -m main
git_quiet -C "$MAIN" worktree add -b feature "$WORKTREE"
echo change > "$WORKTREE/change.txt"
git_quiet -C "$WORKTREE" add change.txt
git_quiet -C "$WORKTREE" commit -m feature
MAIN_HEAD=$(git -C "$MAIN" rev-parse HEAD)
WORKTREE_HEAD=$(git -C "$WORKTREE" rev-parse HEAD)
populate_project "$NOGIT"
NOCOMMIT="$FIXTURE/nocommit"
populate_project "$NOCOMMIT"
git_quiet init "$NOCOMMIT"
# getenforce answering Enforcing makes the script treat the host as SELinux-enforcing.
SELINUX_BIN="$TEMP_DIR/selinux-bin"
mkdir -p "$SELINUX_BIN"
printf '#!/bin/sh\necho Enforcing\n' > "$SELINUX_BIN/getenforce"
chmod +x "$SELINUX_BIN/getenforce"

# --- Helpers -----------------------------------------------------------------------------
STATE=""
OUTPUT=""
STATUS=0
RUNNER_UMASK=022

# Usage: run_runner <project_dir> [VAR=value ...] -- [script args ...]
run_runner() {
  local project=$1
  shift
  local env_args=()
  while [[ "$1" != "--" ]]; do
    env_args+=("$1")
    shift
  done
  shift
  STATE=$(mktemp "$TEMP_DIR/state.XXXXXX")
  OUTPUT=$(mktemp "$TEMP_DIR/output.XXXXXX")
  local work
  work=$(mktemp -d "$TEMP_DIR/work.XXXXXX")
  STATUS=0
  (umask "$RUNNER_UMASK" && cd "$project" && env -u CONTAINER_RUNTIME PATH="$BIN:$PATH" FAKE_STATE="$STATE" FAKE_WORK="$work" \
    GIT_CEILING_DIRECTORIES="$FIXTURE" ${env_args[@]+"${env_args[@]}"} \
    bash "$project/utils/run-containers-tests.sh" --libc=glibc --arch=x64 --jdk=21 --config=debug "$@") \
    > "$OUTPUT" 2>&1 || STATUS=$?
}

state_value() {
  sed -n "s/^$1=//p" "$STATE" | head -n 1
}

has_state() {
  grep -q "^$1=" "$STATE"
}

no_clone_dir_left() {
  ! compgen -G "$1/build/container-source.*" > /dev/null
}

output_contains() {
  grep -qF -- "$1" "$OUTPUT"
}

equals() {
  [[ "$1" == "$2" ]]
}

starts_with() {
  [[ "$1" == "$2"* ]]
}

dump_on_failure() {
  if [[ $FAILED -gt 0 ]]; then
    echo "--- last script output ---" >&2
    cat "$OUTPUT" >&2
    echo "--- last fake runtime state ---" >&2
    cat "$STATE" >&2
  fi
}

# --- Tests -------------------------------------------------------------------------------

test_worktree_clone_mode() {
  check "worktree fixture starts without build/" test ! -e "$WORKTREE/build"
  run_runner "$WORKTREE" -- --container=podman
  check "worktree clone run exits 0 (got $STATUS)" equals "$STATUS" 0
  local host
  host=$(state_value source_host)
  check "worktree /source is a host clone under build/ (got '$host')" \
    starts_with "$host" "$WORKTREE/build/container-source."
  check "worktree /source has a .git directory" equals "$(state_value source_gitdir)" dir
  check "worktree /source is at the worktree HEAD" equals "$(state_value source_head)" "$WORKTREE_HEAD"
  check "worktree HEAD differs from the main checkout HEAD" test "$WORKTREE_HEAD" != "$MAIN_HEAD"
  check "worktree /source can be cloned" equals "$(state_value source_clonable)" yes
  check "worktree run argv has --pids-limit=-1" grep -q "^run_argv=.*--pids-limit=-1" "$STATE"
  check "worktree probe checks .git/HEAD" equals "$(state_value probe_marker)" .git/HEAD
  check "worktree probe mounts the host clone" starts_with "$(state_value probe_vol)" "$host:/probe"
  check "probe and run use the same volume options" \
    equals "$(state_value probe_vol | sed 's|.*:/probe||')" "$(state_value run_vol | sed 's|.*:/source||')"
  check "worktree output logs the source commit" output_contains ">>> Source commit: $WORKTREE_HEAD"
  check "worktree host clone is removed after the run" no_clone_dir_left "$WORKTREE"
}

test_main_checkout_clone_mode() {
  run_runner "$MAIN" -- --container=podman
  check "main clone run exits 0 (got $STATUS)" equals "$STATUS" 0
  check "main /source is a host clone under build/, not the checkout" \
    starts_with "$(state_value source_host)" "$MAIN/build/container-source."
  check "main /source is at the main HEAD" equals "$(state_value source_head)" "$MAIN_HEAD"
  check "main /source can be cloned" equals "$(state_value source_clonable)" yes
  check "main host clone is removed after the run" no_clone_dir_left "$MAIN"
}

test_failed_run_removes_clone() {
  run_runner "$WORKTREE" FAKE_RUN_EXIT=3 -- --container=podman
  check "failed run exits non-zero" test "$STATUS" -ne 0
  check "failed run reached the container run" has_state run_argv
  check "host clone is removed after a failed run" no_clone_dir_left "$WORKTREE"
}

test_terminated_run_removes_clone() {
  run_runner "$WORKTREE" FAKE_RUN_SIGNAL=TERM -- --container=podman
  check "terminated run exits non-zero" test "$STATUS" -ne 0
  check "terminated run reached the container run" has_state run_argv
  check "host clone is removed after SIGTERM" no_clone_dir_left "$WORKTREE"
}

test_probe_statfs_clone_mode() {
  run_runner "$WORKTREE" FAKE_PROBE=statfs -- --container=podman
  check "statfs probe failure exits non-zero" test "$STATUS" -ne 0
  check "statfs probe failure does not start the run" bash -c "! grep -q '^run_argv=' '$STATE'"
  check "statfs probe failure prints the runtime error" output_contains "statfs"
  check "statfs probe failure reports the runtime failure and exit code" \
    output_contains "could not start the probe container for $WORKTREE/build/container-source."
  check "statfs probe failure reports exit 125" output_contains "(exit 125)"
  check "statfs probe failure does not claim a missing marker" bash -c "! grep -q 'not found)' '$OUTPUT'"
  check "statfs probe failure explains the VM share" output_contains "share only some host directories"
  check "host clone is removed after a probe failure" no_clone_dir_left "$WORKTREE"
}

test_probe_empty_mount_docker() {
  run_runner "$MAIN" FAKE_PROBE=empty -- --container=docker
  check "empty-mount probe failure exits non-zero" test "$STATUS" -ne 0
  check "empty-mount probe failure does not start the run" bash -c "! grep -q '^run_argv=' '$STATE'"
  check "empty-mount probe failure reports the missing marker" \
    output_contains "is not visible or not readable inside the container (.git/HEAD not found)"
  check "empty-mount probe failure explains the VM share" output_contains "share only some host directories"
  if [[ ! -r /sys/fs/selinux/enforce ]] && ! command -v getenforce > /dev/null 2>&1; then
    check "no SELinux hint without SELinux" bash -c "! grep -q SELinux '$OUTPUT'"
  fi
}

test_probe_selinux_docker_hint() {
  run_runner "$MAIN" FAKE_PROBE=empty PATH="$SELINUX_BIN:$BIN:$PATH" -- --container=docker
  check "SELinux docker probe failure exits non-zero" test "$STATUS" -ne 0
  check "SELinux docker probe failure suggests podman" output_contains "use --container=podman"
  run_runner "$MAIN" FAKE_PROBE=empty PATH="$SELINUX_BIN:$BIN:$PATH" -- --container=podman
  check "SELinux podman probe relabels the mount" equals "$(state_value probe_vol | sed 's|.*:/probe||')" ":ro,z"
  check "SELinux podman probe failure has no docker hint" bash -c "! grep -q 'use --container=podman' '$OUTPUT'"
}

test_mount_mode() {
  run_runner "$WORKTREE" -- --container=podman --mount
  check "mount run exits 0 (got $STATUS)" equals "$STATUS" 0
  check "mount probe checks the checkout itself" starts_with "$(state_value probe_vol)" "$WORKTREE:/probe"
  check "mount probe checks the wrapper script" equals "$(state_value probe_marker)" gradlew
  check "mount run mounts the checkout at /workspace" starts_with "$(state_value run_vol)" "$WORKTREE:/workspace"
  check "mount run argv has --pids-limit=-1" grep -q "^run_argv=.*--pids-limit=-1" "$STATE"
  check "mount mode creates no host clone" no_clone_dir_left "$WORKTREE"
}

test_mount_mode_probe_failure() {
  run_runner "$WORKTREE" FAKE_PROBE=statfs -- --container=docker --mount
  check "mount probe failure exits non-zero" test "$STATUS" -ne 0
  check "mount probe failure does not start the run" bash -c "! grep -q '^run_argv=' '$STATE'"
  check "mount probe failure names the checkout" output_contains "probe container for $WORKTREE (exit 125)"
}

test_shell_mode() {
  run_runner "$WORKTREE" -- --container=podman --shell
  check "shell run exits 0 (got $STATUS)" equals "$STATUS" 0
  check "shell run argv has --pids-limit=-1 and -it" grep -q "^run_argv=.*--pids-limit=-1.* -it " "$STATE"
  check "host clone is removed after the shell exits" no_clone_dir_left "$WORKTREE"
}

# A user's global git config must not change the host clone: the container's git cannot
# read reftable, and user hooks must not run.
test_host_clone_ignores_global_config() {
  local hooks="$TEMP_DIR/global-hooks" marker="$TEMP_DIR/global-hook-ran"
  mkdir -p "$hooks"
  printf '#!/bin/sh\ntouch "%s"\n' "$marker" > "$hooks/reference-transaction"
  chmod +x "$hooks/reference-transaction"
  printf '[init]\n\tdefaultRefFormat = reftable\n[core]\n\thooksPath = %s\n' "$hooks" > "$TEMP_DIR/gitconfig"
  run_runner "$WORKTREE" GIT_CONFIG_GLOBAL="$TEMP_DIR/gitconfig" -- --container=podman
  check "global-config run exits 0 (got $STATUS)" equals "$STATUS" 0
  check "global core.hooksPath hooks do not run during the host clone" test ! -e "$marker"
  # Before 2.45, rev-parse echoes the unknown option back instead of failing.
  if [[ "$(git -C "$MAIN" rev-parse --show-ref-format 2>/dev/null)" == files ]]; then
    check "host clone uses the files ref format (got '$(state_value source_ref_format)')" \
      equals "$(state_value source_ref_format)" files
  else
    echo "SKIP: host git predates --show-ref-format (2.45); ref format not checked"
  fi
}

test_clone_mode_outside_git() {
  run_runner "$NOGIT" -- --container=podman
  check "clone outside git exits non-zero" test "$STATUS" -ne 0
  check "clone outside git prints the clone error" output_contains "Error: could not clone $NOGIT for the container"
  check "clone outside git fails before any image or container command" test ! -s "$STATE"
  check "clone outside git leaves no clone dir" no_clone_dir_left "$NOGIT"
}

test_clone_mode_without_commit() {
  run_runner "$NOCOMMIT" -- --container=podman
  check "clone without commit exits non-zero" test "$STATUS" -ne 0
  check "clone without commit prints the error" output_contains "Error: $NOCOMMIT has no commit to clone"
  check "clone without commit starts no container" test ! -s "$STATE"
  check "clone without commit leaves no clone dir" no_clone_dir_left "$NOCOMMIT"
}

# A container user that is not the host owner must read the clone even under umask 077.
test_host_clone_readable_under_strict_umask() {
  RUNNER_UMASK=077
  run_runner "$WORKTREE" -- --container=podman
  RUNNER_UMASK=022
  check "umask 077 run exits 0 (got $STATUS)" equals "$STATUS" 0
  check "umask 077 host clone dir is world-readable (got $(state_value source_mode))" \
    equals "$(state_value source_mode)" drwxr-xr-x
  check "umask 077 host clone files are world-readable (got $(state_value source_head_file_mode))" \
    equals "$(state_value source_head_file_mode)" -rw-r--r--
}

test_worktree_clone_mode
test_main_checkout_clone_mode
test_failed_run_removes_clone
test_terminated_run_removes_clone
test_probe_statfs_clone_mode
test_probe_empty_mount_docker
test_probe_selinux_docker_hint
test_mount_mode
test_mount_mode_probe_failure
test_shell_mode
test_host_clone_ignores_global_config
test_clone_mode_outside_git
test_clone_mode_without_commit
test_host_clone_readable_under_strict_umask

dump_on_failure
echo "$TESTS tests, $FAILED failed"
[[ $FAILED -eq 0 ]]
