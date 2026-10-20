#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0

set -euo pipefail

die() {
  echo "ERROR: $*" >&2
  exit 1
}

if [ "$#" -ne 1 ]; then
  die "usage: $0 <assembled-release-jar>"
fi

jar=$1
[ -f "$jar" ] || die "JAR not found: $jar"

for tool in unzip readelf objdump; do
  command -v "$tool" >/dev/null 2>&1 || die "$tool not found"
done

entries=$(unzip -Z1 "$jar" | grep -E '^META-INF/native-libs/linux-(x64|aarch64)/libjavaProfiler\.so$' || true)
entry_count=$(printf '%s\n' "$entries" | grep -c . || true)
[ "$entry_count" -eq 1 ] || die "expected exactly one packaged Linux profiler library, found $entry_count"
entry=$entries

tmp_dir=$(mktemp -d)
trap 'rm -rf "$tmp_dir"' EXIT
so="$tmp_dir/libjavaProfiler.so"
unzip -p "$jar" "$entry" >"$so"
[ -s "$so" ] || die "packaged profiler library is empty: $entry"

machine=$(readelf -hW "$so" | sed -n 's/^[[:space:]]*Machine:[[:space:]]*//p')
case "$machine" in
  *X86-64*)
    expected_args='8@%rdi 8@%rsi 8@%rdx'
    expected_nop='90[[:space:]]+nop'
    instruction_bytes=1
    ;;
  *AArch64*)
    expected_args='8@x0 8@x1 8@x2'
    expected_nop='d503201f[[:space:]]+nop'
    instruction_bytes=4
    ;;
  *)
    die "unsupported ELF machine: $machine"
    ;;
esac

notes=$(readelf -nW "$so")
provider_count=$(printf '%s\n' "$notes" | grep -c 'Provider: ddheap' || true)
alloc_count=$(printf '%s\n' "$notes" | grep -c 'Name: alloc' || true)
[ "$provider_count" -eq 1 ] || die "expected one ddheap provider note, found $provider_count"
[ "$alloc_count" -eq 1 ] || die "expected one alloc probe note, found $alloc_count"
if printf '%s\n' "$notes" | grep -q 'Name: free'; then
  die "unexpected ddheap:free probe in allocation-only artifact"
fi
printf '%s\n' "$notes" | grep -Fq "Arguments: $expected_args" ||
  die "unexpected alloc arguments; expected: $expected_args"

location=$(printf '%s\n' "$notes" | sed -n 's/.*Location: \(0x[[:xdigit:]]*\).*/\1/p')
semaphore=$(printf '%s\n' "$notes" | sed -n 's/.*Semaphore: \(0x[[:xdigit:]]*\).*/\1/p')
[ -n "$location" ] || die "probe location is missing"
[ -n "$semaphore" ] || die "probe semaphore is missing"
(( semaphore != 0 )) || die "probe semaphore address is zero"
(( semaphore % 2 == 0 )) || die "probe semaphore is not 2-byte aligned: $semaphore"

stop=$((location + instruction_bytes))
instruction=$(objdump -d --start-address="$location" --stop-address="$stop" "$so")
printf '%s\n' "$instruction" | grep -Eq "$expected_nop" ||
  die "probe location $location is not the expected architecture NOP"

sections=$(readelf -SW "$so")
printf '%s\n' "$sections" | grep -Fq '.note.stapsdt' || die ".note.stapsdt is missing"
if printf '%s\n' "$sections" | grep -Eq '\.debug_(info|line|abbrev|str)([[:space:]]|$)'; then
  die "packaged release library still contains compiler debug sections"
fi

echo "Verified $entry ($machine): ddheap:alloc at $location, semaphore $semaphore, args $expected_args"
