#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0

set -euo pipefail

script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
tmp_dir=$(mktemp -d)
trap 'rm -rf "$tmp_dir"' EXIT
mkdir -p "$tmp_dir/bin"
cat > "$tmp_dir/bin/ldd" <<'SH'
#!/bin/sh
printf '%s\n' "$LDD_STDOUT"
printf '%s\n' "$LDD_STDERR" >&2
exit "$LDD_STATUS"
SH
chmod +x "$tmp_dir/bin/ldd"

run_make() {
  local stdout=$1 stderr=$2 status=$3
  PATH="$tmp_dir/bin:$PATH" \
    LDD_STDOUT="$stdout" \
    LDD_STDERR="$stderr" \
    LDD_STATUS="$status" \
    make -C "$script_dir" -n all
}

check_gate() {
  local name=$1 expected_ifunc=$2 stdout=$3 stderr=$4 status=$5 output
  output=$(run_make "$stdout" "$stderr" "$status" 2>&1) || {
    printf 'FAIL: %s: make -n failed\n%s\n' "$name" "$output" >&2
    return 1
  }

  if ! grep -Fq 'libddprof-fixture-gnu.so' <<< "$output"; then
    printf 'FAIL: %s: ordinary fixture missing\n%s\n' "$name" "$output" >&2
    return 1
  fi

  if [[ $expected_ifunc == yes ]]; then
    if ! grep -Fq 'libddprof-fixture-ifunc.so' <<< "$output"; then
      printf 'FAIL: %s: ifunc fixture missing\n%s\n' "$name" "$output" >&2
      return 1
    fi
  elif grep -Fq 'libddprof-fixture-ifunc.so' <<< "$output"; then
    printf 'FAIL: %s: ifunc fixture unexpectedly enabled\n%s\n' "$name" "$output" >&2
    return 1
  fi

  printf 'PASS: %s\n' "$name"
}

check_gate 'glibc banner' yes 'ldd GLIBC' '' 0
check_gate 'GNU libc banner' yes 'GNU LIBC release' '' 0
check_gate 'multiple matching lines remain boolean' yes $'glibc\nglibc' '' 0
check_gate 'stderr-only musl banner is not detected' no '' 'musl libc (stderr)' 1
