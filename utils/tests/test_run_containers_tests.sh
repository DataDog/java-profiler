#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc
# Hermetic runner contract tests. Optional argument: a runner copy to test.
# No Dockerfile, container command, download, or Gradle command is executed.
# Package availability and compiler behavior require separate real-image checks.
set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
RUNNER=${1:-"$SCRIPT_DIR/../run-containers-tests.sh"}
TEMP_DIR=$(mktemp -d)
cleanup() {
  local status=$?
  if [ "$status" -eq 0 ]; then
    rm -rf "$TEMP_DIR"
  else
    echo "Evidence retained at $TEMP_DIR" >&2
  fi
}
trap cleanup EXIT
trap 'echo "FAIL: $BASH_COMMAND (line $LINENO); inspect retained evidence" >&2' ERR

mkdir -p "$TEMP_DIR/bin" "$TEMP_DIR/repo/utils" "$TEMP_DIR/repo/gradle"
cp "$RUNNER" "$TEMP_DIR/repo/utils/run-containers-tests.sh"
chmod +x "$TEMP_DIR/repo/utils/run-containers-tests.sh"
# Any accidental attempt to execute Gradle must fail, not be accepted by the mock.
printf '#!/bin/sh\necho "Unexpected Gradle execution" >&2\nexit 99\n' > "$TEMP_DIR/repo/gradlew"
chmod +x "$TEMP_DIR/repo/gradlew"
printf 'wrapper fixture\n' > "$TEMP_DIR/repo/gradle/fixture"
cat > "$TEMP_DIR/bin/docker" <<'FAKE'
#!/usr/bin/env bash
set -euo pipefail
n=$(cat "$FAKE_STATE/counter")
n=$((n + 1))
printf '%s\n' "$n" > "$FAKE_STATE/counter"
printf '%s\n' "$@" > "$FAKE_STATE/call-$n.argv"
printf '%s %s\n' "${0##*/}" "$1" >> "$FAKE_STATE/calls"
case "$1" in
  image)
    [ "$#" -eq 3 ] && [ "$2" = inspect ] || exit 90
    printf '%s\n' "$3" >> "$FAKE_STATE/inspected"
    grep -Fxq -- "$3" "$FAKE_STATE/cache"
    ;;
  build)
    shift
    tag= recipe= platform= context=
    while [ "$#" -gt 0 ]; do
      case "$1" in
        -t) tag=$2; shift 2 ;;
        -f) recipe=$2; shift 2 ;;
        --platform) platform=$2; shift 2 ;;
        *) [ "$#" -eq 1 ] || exit 91; context=$1; shift ;;
      esac
    done
    [ -n "$tag" ] && [ -n "$platform" ] && [ -f "$recipe" ] || exit 92
    [ -f "$context/gradlew" ] && [ -f "$context/gradle/fixture" ] || exit 93
    cp "$recipe" "$FAKE_STATE/build-$n.Dockerfile"
    printf '%s\n' "$tag" >> "$FAKE_STATE/build-tags"
    printf '%s\n' "$FAKE_STATE/build-$n.Dockerfile" >> "$FAKE_STATE/build-files"
    printf '%s\n' "$tag" >> "$FAKE_STATE/cache"
    ;;
  run)
    printf '%s\n' "$FAKE_STATE/call-$n.argv" >> "$FAKE_STATE/run-files"
    for arg in "$@"; do last=$arg; done
    printf '%s\n' "$last" >> "$FAKE_STATE/run-commands"
    if [ -n "${FAKE_RUN_FAIL_MATCH:-}" ] && [[ "$last" == *"$FAKE_RUN_FAIL_MATCH"* ]]; then
      exit 42
    fi
    ;;
  *) echo "Unsupported fake-runtime command: $*" >&2; exit 94 ;;
esac
FAKE
cp "$TEMP_DIR/bin/docker" "$TEMP_DIR/bin/podman"
cat > "$TEMP_DIR/bin/uname" <<'FAKE'
#!/bin/sh
[ "$1" = -m ] || exit 95
printf '%s\n' "$FAKE_MACHINE"
FAKE
cat > "$TEMP_DIR/bin/getenforce" <<'FAKE'
#!/bin/sh
printf '%s\n' "$FAKE_SELINUX"
FAKE
chmod +x "$TEMP_DIR/bin/"*
export PATH="$TEMP_DIR/bin:$PATH"
export CONTAINER_RUNTIME=podman FAKE_MACHINE=x86_64 FAKE_SELINUX=Disabled
unset FAKE_RUN_FAIL_MATCH
CASE=0
CHECKS=0
new_case() {
  CASE=$((CASE + 1))
  export FAKE_STATE="$TEMP_DIR/case-$CASE"
  mkdir -p "$FAKE_STATE"
  printf '0\n' > "$FAKE_STATE/counter"
  local file
  for file in cache calls inspected build-tags build-files run-files run-commands; do
    : > "$FAKE_STATE/$file"
  done
}
run_runner() {
  if ! "$TEMP_DIR/repo/utils/run-containers-tests.sh" "$@" </dev/null > "$FAKE_STATE/output" 2>&1; then
    echo "FAIL: runner $*; inspect $FAKE_STATE/output" >&2
    exit 1
  fi
}
expect_error() {
  local message=$1
  shift
  if "$TEMP_DIR/repo/utils/run-containers-tests.sh" "$@" </dev/null > "$FAKE_STATE/output" 2>&1; then
    echo "FAIL: runner $* unexpectedly passed" >&2
    exit 1
  fi
  has "$FAKE_STATE/output" "$message"
}
has() {
  CHECKS=$((CHECKS + 1))
  if ! grep -Fq -- "$2" "$1"; then
    echo "FAIL: $1 must contain: $2" >&2
    exit 1
  fi
}
lacks() {
  CHECKS=$((CHECKS + 1))
  if grep -Fq -- "$2" "$1"; then
    echo "FAIL: $1 must not contain: $2" >&2
    exit 1
  fi
}
lines() {
  CHECKS=$((CHECKS + 1))
  local count
  count=$(wc -l < "$1" | tr -d ' ')
  if [ "$count" != "$2" ]; then
    echo "FAIL: $1 expected $2 lines, got $count" >&2
    exit 1
  fi
}
last_run() { tail -n 1 "$FAKE_STATE/run-files"; }

# Legacy tags must miss at BOTH cache levels; new tags must hit on the next run.
for arch in x64 aarch64; do
  new_case
  base="java-profiler-base:glibc-$arch-clang17"
  image="java-profiler-test:glibc-jdk21-$arch-clang17"
  printf '%s\n' "java-profiler-base:glibc-$arch" "java-profiler-test:glibc-jdk21-$arch" > "$FAKE_STATE/cache"
  run_runner --container=docker --libc=glibc --arch="$arch"
  lines "$FAKE_STATE/build-tags" 2
  has "$FAKE_STATE/build-tags" "$base"
  has "$FAKE_STATE/build-tags" "$image"
  has "$FAKE_STATE/inspected" "$base"
  has "$FAKE_STATE/inspected" "$image"
  recipe=$(head -n 1 "$FAKE_STATE/build-files")
  has "$recipe" 'FROM ubuntu:22.04'
  has "$recipe" 'llvm-toolchain-jammy-17 main'
  has "$recipe" 'apt-get install -y --no-install-recommends clang-17 libclang-rt-17-dev'
  has "$recipe" 'update-alternatives --install /usr/bin/clang clang /usr/bin/clang-17 170'
  has "$recipe" '--slave /usr/bin/clang++ clang++ /usr/bin/clang++-17'
  has "$recipe" 'update-alternatives --set clang /usr/bin/clang-17'
  lacks "$recipe" 'libclang-dev'
  lacks "$recipe" 'g++ clang git'
  if [ "$arch" = x64 ]; then
    x64_recipe=$recipe
    platform=linux/amd64
  else
    cmp "$x64_recipe" "$recipe"
    platform=linux/arm64
  fi
  has "$FAKE_STATE/call-2.argv" "$platform"
  has "$(last_run)" "$platform"
  has "$(last_run)" "$image"
  jdk_recipe=$(tail -n 1 "$FAKE_STATE/build-files")
  has "$jdk_recipe" "FROM $base"
  has "$jdk_recipe" 'ENV JAVA_HOME=/jdk'
  has "$jdk_recipe" 'ENV JAVA_TEST_HOME=/jdk'
  has "$FAKE_STATE/run-commands" 'git config --global --add safe.directory /source/.git && git clone --depth 1 file:///source /workspace'
  has "$(last_run)" "$TEMP_DIR/repo:/source:ro"
  has "$FAKE_STATE/run-commands" ':ddprof-test:testDebug -Pskip-gtest'
  lacks "$(last_run)" '--privileged'
  lacks "$FAKE_STATE/run-commands" 'sysctl'
  lacks "$FAKE_STATE/run-commands" 'native.forceCompiler'

  run_runner --container=docker --libc=glibc --arch="$arch"
  lines "$FAKE_STATE/build-tags" 2
  has "$FAKE_STATE/output" 'Using cached base image:'
  has "$FAKE_STATE/output" 'Using cached image:'

  # Base-only rebuild intentionally still reuses the cached JDK image.
  run_runner --container=docker --libc=glibc --arch="$arch" --rebuild-base
  lines "$FAKE_STATE/build-tags" 3
  [ "$(tail -n 1 "$FAKE_STATE/build-tags")" = "$base" ]
  has "$FAKE_STATE/output" 'Using cached image:'
  # Full rebuild bypasses both inspect calls, not just the base cache.
  inspected=$(wc -l < "$FAKE_STATE/inspected" | tr -d ' ')
  run_runner --container=docker --libc=glibc --arch="$arch" --rebuild
  lines "$FAKE_STATE/inspected" "$inspected"
  lines "$FAKE_STATE/build-tags" 5
  [ "$(tail -n 1 "$FAKE_STATE/build-tags")" = "$image" ]
done

# A cached base without a JDK image builds only the JDK layer (two-JDK variant).
new_case
printf '%s\n' 'java-profiler-base:glibc-aarch64-clang17' > "$FAKE_STATE/cache"
run_runner --arch=aarch64 --jdk=17-j9 --config=asan --gtest-task=elfparser_ut --mount
lines "$FAKE_STATE/build-tags" 1
recipe=$(head -n 1 "$FAKE_STATE/build-files")
has "$recipe" 'ENV JAVA_HOME=/jdk-build'
has "$recipe" 'ENV JAVA_TEST_HOME=/jdk-test'
has "$recipe" 'OpenJDK21U-jdk_aarch64_linux_hotspot'
has "$recipe" 'ibm-semeru-open-jdk_aarch64_linux_17'
has "$FAKE_STATE/run-commands" ':ddprof-lib:gtestAsan_elfparser_ut'
lacks "$FAKE_STATE/run-commands" 'git clone'
has "$(last_run)" "$TEMP_DIR/repo:/workspace"
has "$FAKE_STATE/calls" 'podman run'
lacks "$(last_run)" '--privileged'

# Musl tags and recipe remain Alpine/clang/compiler-rt, not the glibc toolchain.
cat > "$TEMP_DIR/expected-musl.Dockerfile" <<'EOF'
FROM alpine:3.21

# Install build dependencies
# - linux-headers provides linux/limits.h
# - compiler-rt provides sanitizer runtimes (ASan, TSan) for clang
# - llvm provides libFuzzer
# - openssh-client for git clone over SSH
RUN apk update && \
    apk add --no-cache \
        curl wget bash make g++ clang git jq cmake coreutils \
        gtest-dev gmock tar binutils musl-dbg linux-headers \
        compiler-rt llvm openssh-client gdb

# Set up Gradle cache directory
ENV GRADLE_USER_HOME=/gradle-cache
RUN mkdir -p /gradle-cache

WORKDIR /workspace
EOF
for arch in x64 aarch64; do
  new_case
  run_runner --libc=musl --arch="$arch" --jdk=17 --config=release --tests=ExampleTest
  lines "$FAKE_STATE/build-tags" 2
  has "$FAKE_STATE/build-tags" "java-profiler-base:musl-$arch"
  has "$FAKE_STATE/build-tags" "java-profiler-test:musl-jdk17-$arch"
  lacks "$FAKE_STATE/build-tags" 'clang17'
  recipe=$(head -n 1 "$FAKE_STATE/build-files")
  cmp "$TEMP_DIR/expected-musl.Dockerfile" "$recipe"
  has "$recipe" 'FROM alpine:3.21'
  has "$recipe" 'g++ clang git jq cmake coreutils'
  has "$recipe" 'compiler-rt llvm openssh-client gdb'
  lacks "$recipe" 'apt.llvm.org'
  lacks "$recipe" 'update-alternatives'
  recipe=$(tail -n 1 "$FAKE_STATE/build-files")
  has "$recipe" "linux-$arch-musl-lite.tar.gz"
  has "$recipe" 'ENV JAVA_HOME=/jdk-build'
  has "$recipe" 'ENV JAVA_TEST_HOME=/jdk-test'
  has "$FAKE_STATE/run-commands" ':ddprof-test:testRelease -Ptests=ExampleTest -Pskip-gtest'
  lacks "$(last_run)" '--privileged'
  run_runner --libc=musl --arch="$arch" --jdk=17
  lines "$FAKE_STATE/build-tags" 2
done

# TSan's forceCompiler, sysctl prefix and privilege are generated ONLY for arm64.
# The fake runtime records these strings but never executes them.
for arch in aarch64 x64; do
  new_case
  run_runner --container=docker --arch="$arch" --config=tsan --gtest-task=elfparser_ut
  has "$FAKE_STATE/run-commands" ':ddprof-lib:gtestTsan_elfparser_ut'
  if [ "$arch" = aarch64 ]; then
    has "$FAKE_STATE/run-commands" '-Pnative.forceCompiler=clang++-17'
    has "$FAKE_STATE/run-commands" 'sysctl -w vm.mmap_rnd_bits=28 2>/dev/null || true && '
    has "$(last_run)" '--privileged'
  else
    lacks "$FAKE_STATE/run-commands" 'native.forceCompiler'
    lacks "$FAKE_STATE/run-commands" 'sysctl'
    lacks "$(last_run)" '--privileged'
  fi
done

# Architecture auto-detection aliases/fallback; environment runtime and CLI override.
for machine in arm64 aarch64 amd64 x86_64 unknown; do
  new_case
  export FAKE_MACHINE=$machine
  run_runner --shell --mount --container=docker
  case "$machine" in arm64|aarch64) platform=linux/arm64 ;; *) platform=linux/amd64 ;; esac
  has "$(last_run)" "$platform"
  has "$(last_run)" '--cap-add=SYS_PTRACE'
  has "$(last_run)" '-it'
  has "$FAKE_STATE/calls" 'docker run'
  lacks "$FAKE_STATE/run-commands" 'gradlew'
  lacks "$FAKE_STATE/run-commands" 'safe.directory'
done
export FAKE_MACHINE=x86_64
new_case
run_runner --shell --arch=x64
has "$FAKE_STATE/run-commands" 'safe.directory /source/.git'
has "$FAKE_STATE/run-commands" 'cd /workspace && /bin/bash'
has "$FAKE_STATE/calls" 'podman run'
# getenforce is consulted only if the kernel does not expose the SELinux flag.
if [ ! -r /sys/fs/selinux/enforce ]; then
  export FAKE_SELINUX=Enforcing
  new_case
  run_runner --arch=x64
  has "$(last_run)" "$TEMP_DIR/repo:/source:ro,z"
  run_runner --arch=x64 --mount
  has "$(last_run)" "$TEMP_DIR/repo:/workspace:z"
  export FAKE_SELINUX=Disabled
fi

# Matrix preview/filtering must not invoke a runtime. Cover each skip rule.
new_case
run_runner --libc=all --arch=all --jdk=8,11,21,21-j9,21-graal --config=debug,asan,tsan
lines "$FAKE_STATE/calls" 0
has "$FAKE_STATE/output" 'J9/OpenJ9 is not available for musl libc'
has "$FAKE_STATE/output" 'GraalVM is not available for musl libc'
has "$FAKE_STATE/output" 'GraalVM is not compatible with ASan shadow memory ranges'
has "$FAKE_STATE/output" 'HotSpot 8/11 are skipped on glibc aarch64 in CI'
has "$FAKE_STATE/output" 'sanitizer configs are filtered out for musl in CI'
has "$FAKE_STATE/output" 'Preview only. Add --run'

# Forward runtime, mount, test selection, gtest, and rebuild through real child calls.
new_case
run_runner --libc=glibc --arch=x64 --jdk=17,21 --config=debug --run --container=docker --mount --tests=ExampleTest --gtest --rebuild
lines "$FAKE_STATE/run-files" 2
lines "$FAKE_STATE/build-tags" 4
lines "$FAKE_STATE/inspected" 0
has "$FAKE_STATE/run-commands" '-Ptests=ExampleTest'
lacks "$FAKE_STATE/run-commands" '-Pskip-gtest'
lacks "$FAKE_STATE/run-commands" 'git clone'
lacks "$FAKE_STATE/calls" 'podman'
has "$TEMP_DIR/repo/build/reports/container-matrix/summary.json" '"passed": 2, "failed": 0'

new_case
printf '%s\n' 'java-profiler-base:glibc-x64-clang17' 'java-profiler-test:glibc-jdk21-x64-clang17' > "$FAKE_STATE/cache"
run_runner --arch=x64 --jdk=21 --config=debug,asan --run --gtest-task=elfparser_ut --rebuild-base
lines "$FAKE_STATE/build-tags" 2
has "$FAKE_STATE/run-commands" ':ddprof-lib:gtestDebug_elfparser_ut'
has "$FAKE_STATE/run-commands" ':ddprof-lib:gtestAsan_elfparser_ut'

new_case
export FAKE_RUN_FAIL_MATCH=gtestDebug
expect_error 'Stopping after first failure' --arch=x64 --config=debug,release --run --gtest-task=elfparser_ut --fail-fast
lines "$FAKE_STATE/run-files" 1
has "$TEMP_DIR/repo/build/reports/container-matrix/summary.json" '"failed": 1, "skipped": 0, "cancelled": 1'
unset FAKE_RUN_FAIL_MATCH

# Validation errors are expected failures, not mocked successes.
new_case
expect_error 'no runnable cells' --libc=musl --config=asan --arch=x64
expect_error 'full --gtest-task paths are not supported' --arch=x64 --config=debug,asan --gtest-task=:ddprof-lib:gtestAsan_elfparser_ut
expect_error '--tests cannot be combined with --gtest-task' --tests=ExampleTest --gtest-task=elfparser_ut
expect_error '--shell is interactive' --arch=all --shell
expect_error '--fail-fast is only valid' --arch=x64 --fail-fast
expect_error '--jdk contains an empty value' --jdk=17,,21
lines "$FAKE_STATE/calls" 0
new_case
run_runner --arch=x64 --gtest-task=:ddprof-lib:gtestDebug_elfparser_ut
has "$FAKE_STATE/run-commands" ':ddprof-lib:gtestDebug_elfparser_ut'

printf 'PASS: %s runner contract checks (%s cases); no real containers, packages, or Gradle executed\n' "$CHECKS" "$CASE"
