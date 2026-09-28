#! /bin/bash
#
# Checks what the shipped library requires from the host that loads it:
#
#   1. the highest versioned glibc symbol it references, which decides the
#      oldest glibc it can run on, and
#   2. the shared libraries it needs at run time.
#
# Both are decided by the build image rather than by anything in the source, so
# either can move without a source change: a newer base image raises the symbol
# versions, and a dropped -static-libstdc++ adds a libstdc++ dependency the host
# JVM's environment may not satisfy. Asserting them where the artifact is built
# keeps the floor a stated contract instead of a property of whichever toolchain
# the pipeline happened to pull.
#
# Usage: check-abi-floor.sh <shared-object> <max-glibc-version>
#   e.g. check-abi-floor.sh libs/linux-x64/libjavaProfiler.so 2.27
#
# Set OBJDUMP to point at a different binutils objdump; the unit tests use it to
# feed canned output in.

set -eo pipefail

SO="$1"
FLOOR="$2"
OBJDUMP="${OBJDUMP:-objdump}"

# Run-time dependencies the shipped library may have. libstdc++ and libgcc are
# deliberately absent: release builds link them statically (see
# ConfigurationPresets.kt), so either one appearing here means the library has
# started needing a C++ runtime from the host. Both loader names are listed
# because one list covers both architectures.
ALLOWED_NEEDED=(
  libc.so.6
  libm.so.6
  libdl.so.2
  libpthread.so.0
  librt.so.1
  ld-linux-x86-64.so.2
  ld-linux-aarch64.so.1
)

die() {
  echo "ERROR: $*" >&2
  exit 1
}

if [ -z "${SO}" ] || [ -z "${FLOOR}" ]; then
  echo "usage: $(basename "$0") <shared-object> <max-glibc-version>" >&2
  exit 2
fi

[ -f "${SO}" ] || die "no such file: ${SO}"
command -v "${OBJDUMP}" >/dev/null 2>&1 || die "${OBJDUMP} not found"

# Higher of two GLIBC_x.y.z tags. sort -V compares component-wise and
# numerically, so GLIBC_2.2.5 orders below GLIBC_2.17; a lexical sort reverses
# exactly that pair and would let a real regression through.
higher_of() {
  printf '%s\n%s\n' "$1" "$2" | sort -V | tail -1
}

# Every comparison below is only as good as `sort -V`. A sort without version
# ordering compares these lexically and inverts exactly this pair, which would
# make the check quietly permissive rather than noisy, so establish that it
# works before trusting it.
if [ "$(higher_of GLIBC_2.2.5 GLIBC_2.17)" != "GLIBC_2.17" ]; then
  die "sort here does not order versions (sort -V); cannot compare glibc versions"
fi

FLOOR_TAG="GLIBC_${FLOOR}"
STATUS=0

# Read the tables first, so "objdump could not read this file" stays separable
# from "objdump read it and found nothing" -- the two need different messages,
# and under `set -eo pipefail` a failing stage inside the parse pipeline below
# would otherwise abort the script with no output at all.
DYNSYM=$("${OBJDUMP}" -T "${SO}") || die "${OBJDUMP} -T failed on ${SO}"

# "<version> <symbol>" for every undefined versioned reference. Matched on the
# trailing fields rather than by column number: objdump adds a weak-binding
# column for some symbols, which shifts every field to its right.
#
# The version is parenthesised when the reference is not to the default version
# -- which is exactly what a .symver pin produces (see glibcCompat.h) -- and
# bare otherwise, so both forms have to parse. Reading only the bare form makes
# a pinned artifact look like it references no versioned symbols at all.
#
# `|| true` keeps a no-match grep from ending the script before the check below
# reports it properly.
REFS=$(printf '%s\n' "${DYNSYM}" \
       | grep -F '*UND*' \
       | sed -nE 's/.*[[:space:]]\(?(GLIBC_[0-9][0-9.]*)\)?[[:space:]]+([^[:space:]]+)[[:space:]]*$/\1 \2/p' \
       || true)

if [ -z "${REFS}" ]; then
  echo "ERROR: ${SO} references no versioned glibc symbols." >&2
  echo "       Every glibc build has some, so this is far more likely to mean the" >&2
  echo "       wrong file was passed or ${OBJDUMP} could not read it than that the" >&2
  echo "       library is clean. Refusing to report a pass." >&2
  exit 1
fi

MAX=$(printf '%s\n' "${REFS}" | awk '{ print $1 }' | sort -u -V | tail -1)

if [ "$(higher_of "${MAX}" "${FLOOR_TAG}")" != "${FLOOR_TAG}" ]; then
  echo "FAIL: ${SO} requires ${MAX}, above the declared floor ${FLOOR_TAG}." >&2
  echo "      Raising the floor drops hosts, so either pin these symbols to an" >&2
  echo "      older version or raise SHIPPED_GLIBC_FLOOR deliberately:" >&2
  {
    printf '%s\n' "${REFS}" | while read -r version symbol; do
      if [ "$(higher_of "${version}" "${FLOOR_TAG}")" != "${FLOOR_TAG}" ]; then
        echo "        ${symbol}@${version}"
      fi
    done | sort -u
  } >&2
  STATUS=1
else
  echo "OK: ${SO} requires at most ${MAX} (floor ${FLOOR_TAG})"
fi

HEADERS=$("${OBJDUMP}" -p "${SO}") || die "${OBJDUMP} -p failed on ${SO}"
NEEDED=$(printf '%s\n' "${HEADERS}" | awk '$1 == "NEEDED" { print $2 }')

if [ -z "${NEEDED}" ]; then
  echo "ERROR: ${SO} declares no NEEDED entries." >&2
  echo "       A dynamically linked library always has some; as above, this points" >&2
  echo "       at an unreadable or wrong file rather than at a clean result." >&2
  exit 1
fi

UNEXPECTED=""
while read -r lib; do
  [ -n "${lib}" ] || continue
  found=0
  for allowed in "${ALLOWED_NEEDED[@]}"; do
    if [ "${lib}" = "${allowed}" ]; then
      found=1
      break
    fi
  done
  [ "${found}" -eq 1 ] || UNEXPECTED="${UNEXPECTED} ${lib}"
done <<EOF
${NEEDED}
EOF

if [ -n "${UNEXPECTED}" ]; then
  echo "FAIL: ${SO} needs shared libraries outside the allowed set:" >&2
  for lib in ${UNEXPECTED}; do
    echo "        ${lib}" >&2
  done
  echo "      libstdc++/libgcc here means the static-link flags were lost, which" >&2
  echo "      makes the library depend on a C++ runtime the host may not have." >&2
  STATUS=1
else
  echo "OK: ${SO} needs only allowed shared libraries"
fi

exit "${STATUS}"
