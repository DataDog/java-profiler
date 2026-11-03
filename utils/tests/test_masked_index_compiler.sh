#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc
# Linux compiler smoke: run inside an already provisioned glibc image.
# Usage: bash utils/tests/test_masked_index_compiler.sh [clang++|clang++-17|clang++-14]
# Clang 14.0.0 on aarch64 is an expected failing comparison, not a passing test.
set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
CXX=${1:-clang++}
if [ "$#" -gt 1 ] || [ "$(uname -s)" != Linux ]; then
  echo "Usage: $0 [compiler]; requires Linux glibc and installed compiler-rt" >&2
  exit 2
fi
case "$(uname -m)" in
  aarch64|arm64) RUNTIME_ARCH=aarch64 ;;
  x86_64|amd64) RUNTIME_ARCH=x86_64 ;;
  *) echo "Unsupported architecture: $(uname -m)" >&2; exit 2 ;;
esac

TEMP_DIR=$(mktemp -d)
cleanup() {
  local status=$?
  if [ "$status" -eq 0 ]; then
    rm -rf "$TEMP_DIR"
  else
    echo "Compiler smoke evidence retained at $TEMP_DIR" >&2
  fi
}
trap cleanup EXIT
trap 'echo "Failed command: $BASH_COMMAND; inspect compiler/runtime identity and retained evidence" >&2' ERR
"$CXX" --version
"$CXX" -print-resource-dir
RUNTIME=$("$CXX" -print-file-name="libclang_rt.asan-$RUNTIME_ARCH.so")
EMBEDDED_RUNTIME=$("$CXX" -print-file-name="libclang_rt.asan-$RUNTIME_ARCH.a")
printf 'ASan shared runtime: %s\nASan executable runtime: %s\n' "$RUNTIME" "$EMBEDDED_RUNTIME"
for runtime in "$RUNTIME" "$EMBEDDED_RUNTIME"; do
  if [ ! -f "$runtime" ]; then
    echo "Missing matching compiler-rt: $runtime; install the runtime for $CXX" >&2
    exit 2
  fi
done

# Full Linux ASan + common compile flags from ConfigurationPresets.kt.
# No -O flag: the project sanitizer preset uses the compiler's default (-O0).
FLAGS=(
  -g -DDEBUG -fPIC
  -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all
  -fsanitize=float-divide-by-zero -fstack-protector-all -fsanitize=leak
  -fsanitize=pointer-overflow -fsanitize=return -fsanitize=bounds
  -fsanitize=alignment -fsanitize=object-size
  -fno-omit-frame-pointer -fno-optimize-sibling-calls
  -fPIC -fno-omit-frame-pointer -momit-leaf-frame-pointer -fvisibility=hidden
  -fdata-sections -ffunction-sections -std=c++17
  '-DPROFILER_VERSION="compiler-smoke"' -DCOUNTERS
)
# Like GtestTaskBuilder's standalone executables, let the compiler embed its
# sanitizer runtime; do not mix it with an explicitly linked shared ASan runtime.
LINK_FLAGS=(
  -ldl -Wl,-z,defs --verbose -lpthread -lm -lrt -Wl,--build-id
  -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
)
printf '%q ' "$CXX" "${FLAGS[@]}" "$SCRIPT_DIR/masked_index_probe.cpp" "${LINK_FLAGS[@]}" -o "$TEMP_DIR/masked_index_probe"
printf '\n'
"$CXX" "${FLAGS[@]}" "$SCRIPT_DIR/masked_index_probe.cpp" "${LINK_FLAGS[@]}" -o "$TEMP_DIR/masked_index_probe"
# Do not suppress bounds diagnostics or inherit an unrelated preloaded runtime.
env -u LD_PRELOAD ASAN_OPTIONS=halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1 \
  "$TEMP_DIR/masked_index_probe"
