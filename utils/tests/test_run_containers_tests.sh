#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc
# Check generated toolchain recipes and cache tags without executing containers.
set -Eeuo pipefail

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
trap 'echo "FAIL: $BASH_COMMAND (line $LINENO)" >&2' ERR

mkdir -p "$TEMP_DIR/repo/utils" "$TEMP_DIR/repo/gradle"
cp "$RUNNER" "$TEMP_DIR/repo/utils/run-containers-tests.sh"
printf '#!/bin/sh\nexit 99\n' > "$TEMP_DIR/repo/gradlew"
cat > "$TEMP_DIR/docker" <<'FAKE'
#!/usr/bin/env bash
set -euo pipefail
case "$1" in
  image)
    grep -Fxq -- "$3" "$CAPTURE/cache"
    ;;
  build)
    shift
    while [ "$#" -gt 0 ]; do
      case "$1" in
        -t) tag=$2; shift 2 ;;
        -f) recipe=$2; shift 2 ;;
        --platform) shift 2 ;;
        *) [ "$#" -eq 1 ] || exit 90; shift ;;
      esac
    done
    cp "$recipe" "$CAPTURE/${recipe##*/}"
    printf '%s\n' "$tag" >> "$CAPTURE/builds"
    printf '%s\n' "$tag" >> "$CAPTURE/cache"
    ;;
  run)
    printf '%s\n' "$@" > "$CAPTURE/run"
    ;;
  *) exit 91 ;;
esac
FAKE
chmod +x "$TEMP_DIR/docker" "$TEMP_DIR/repo/gradlew"
export PATH="$TEMP_DIR:$PATH"

has() {
  if ! grep -Fq -- "$2" "$1"; then
    echo "FAIL: $1 must contain: $2" >&2
    exit 1
  fi
}
run_runner() {
  bash "$TEMP_DIR/repo/utils/run-containers-tests.sh" \
    --container=docker --libc="$libc" --arch="$arch" \
    --jdk=21 --shell --mount "$@" > "$CAPTURE/output" 2>&1
}

for arch in x64 aarch64; do
  for libc in glibc musl; do
    export CAPTURE="$TEMP_DIR/$libc-$arch"
    mkdir "$CAPTURE"
    : > "$CAPTURE/cache"
    : > "$CAPTURE/builds"
    suffix=""
    if [ "$libc" = glibc ]; then
      suffix="-clang17-cov1"
      printf '%s\n' "java-profiler-base:glibc-$arch" \
        "java-profiler-test:glibc-jdk21-$arch" \
        "java-profiler-base:glibc-$arch-clang17" \
        "java-profiler-test:glibc-jdk21-$arch-clang17" > "$CAPTURE/cache"
    fi
    base="java-profiler-base:$libc-$arch$suffix"
    image="java-profiler-test:$libc-jdk21-$arch$suffix"
    run_runner
    test "$(wc -l < "$CAPTURE/builds" | tr -d ' ')" -eq 2
    has "$CAPTURE/builds" "$base"
    has "$CAPTURE/builds" "$image"
    has "$CAPTURE/Dockerfile" "FROM $base"
    has "$CAPTURE/run" "$image"
    recipe="$CAPTURE/Dockerfile.base"
    if [ "$libc" = glibc ]; then
      has "$recipe" 'FROM ubuntu:22.04'
      has "$recipe" 'llvm-toolchain-jammy-17 main'
      has "$recipe" 'apt-get install -y --no-install-recommends clang-17 libclang-rt-17-dev llvm-17'
      has "$recipe" 'pip3 install --no-cache-dir gcovr'
      has "$recipe" 'update-alternatives --install /usr/bin/clang clang /usr/bin/clang-17 170'
      has "$recipe" '--slave /usr/bin/clang++ clang++ /usr/bin/clang++-17'
      has "$recipe" '--slave /usr/bin/llvm-cov llvm-cov /usr/bin/llvm-cov-17'
      has "$recipe" 'update-alternatives --set clang /usr/bin/clang-17'
      if grep -Eq 'g\+\+ clang git|libclang-dev' "$recipe"; then
        echo 'FAIL: legacy Clang packages remain in the glibc recipe' >&2
        exit 1
      fi
    else
      has "$recipe" 'FROM alpine:3.21'
      has "$recipe" 'g++ clang git jq cmake coreutils'
      has "$recipe" 'compiler-rt llvm openssh-client gdb py3-pip'
      has "$recipe" 'pip install --no-cache-dir --break-system-packages gcovr'
      if grep -Eq 'apt\.llvm\.org|update-alternatives|clang-17' "$recipe"; then
        echo 'FAIL: glibc toolchain leaked into the musl recipe' >&2
        exit 1
      fi
    fi
    run_runner
    test "$(wc -l < "$CAPTURE/builds" | tr -d ' ')" -eq 2
    has "$CAPTURE/output" 'Using cached base image:'
    has "$CAPTURE/output" 'Using cached image:'
    run_runner --rebuild-base
    if grep -Fq 'Using cached image:' "$CAPTURE/output"; then
      echo 'FAIL: rebuilt base reused a stale JDK image' >&2
      exit 1
    fi
    test "$(wc -l < "$CAPTURE/builds" | tr -d ' ')" -eq 4
  done
done
printf 'PASS: glibc toolchain/cache migration and unchanged musl defaults (4 configurations)\n'
