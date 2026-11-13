#! /bin/bash
# Copyright 2026, Datadog, Inc.
#
# Network-free tests for the PR comment that
# .gitlab/reliability/post-pr-comment.sh renders. The body is captured through
# the COMMENT_BODY_FILE seam, so nothing is posted; the production posting path
# (seam unset) is asserted separately against a stubbed upsert script.
# Run with: bash .gitlab/reliability/tests/post_pr_comment_test.sh

set -uo pipefail

HERE=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )
SCRIPT="${HERE}/../post-pr-comment.sh"

FAILED=0
WORK=$(mktemp -d)
# shellcheck disable=SC2329  # cleanup runs through the EXIT trap
cleanup() { rm -rf "${WORK}"; }
trap cleanup EXIT

pass() { echo "PASS: $1"; }
fail_case() { echo "FAIL: $1"; FAILED=1; }

BODY="${WORK}/body.md"
SCRIPT_EXIT=0

# Runs the script under test with the given env assignments; the rendered body
# lands in ${BODY} and the exit status in SCRIPT_EXIT.
run_script() {
  : > "${BODY}"
  SCRIPT_EXIT=0
  env "$@" COMMENT_BODY_FILE="${BODY}" DDPROF_COMMIT_BRANCH=pr-branch \
    bash "${SCRIPT}" >"${WORK}/log.txt" 2>&1 || SCRIPT_EXIT=$?
}

assert_exit() { # $1 description, $2 expected exit
  if [ "${SCRIPT_EXIT}" -eq "$2" ]; then
    pass "$1"
  else
    fail_case "$1: expected exit $2, got ${SCRIPT_EXIT}"
  fi
}

assert_body_contains() { # $1 description, $2 fixed needle
  if grep -qF -- "$2" "${BODY}"; then
    pass "$1"
  else
    fail_case "$1: body lacks [$2]"
  fi
}

assert_body_lacks() { # $1 description, $2 fixed needle
  if [ ! -s "${BODY}" ]; then
    fail_case "$1: no body was rendered, so the absence proves nothing"
    return
  fi
  if grep -qF -- "$2" "${BODY}"; then
    fail_case "$1: body unexpectedly contains [$2]"
  else
    pass "$1"
  fi
}

# --- unchanged REASON_* rendering, against a body recorded before the change -

# The expected body below is the rendering the script produced for exactly
# these fixtures before the inconclusive support was added; it pins the
# jit/memory/chaos details blocks byte-for-byte.
cat > "${WORK}/expected" <<'EOF'
## Reliability & Chaos Results

❌ **3 failure(s) detected**  Pipeline: https://x/pipeline/1

<details><summary>❌ profiler gmalloc amd64Xjit</summary>

```
jit crash
second line
```

</details>
<details><summary>❌ profiler jemalloc amd64Xmemory</summary>

```
Memory usage is trending up
extra detail
```

</details>
<details><summary>❌ chaos: profiler gmalloc aarch64Xchaos</summary>

```
chaos timeout
second
```

</details>
EOF

run_script REASON_profiler_gmalloc_amd64Xjit='jit crash;second line' \
           REASON_profiler_jemalloc_amd64Xmemory='Memory usage is trending up;extra detail' \
           REASON_profiler_gmalloc_aarch64Xchaos='chaos timeout;second' \
           CI_PIPELINE_URL='https://x/pipeline/1'
assert_exit "a failure-only run exits 0" 0
if diff -u "${WORK}/expected" "${BODY}" >"${WORK}/diff.txt"; then
  pass "the REASON_ jit/memory/chaos rendering matches the recorded expectation"
else
  fail_case "the REASON_ jit/memory/chaos rendering drifted from the recorded expectation"
  sed 's/^/      /' "${WORK}/diff.txt" | head -20
fi

# --- only INCONCLUSIVE_*Xmemory keys ------------------------------------------

run_script INCONCLUSIVE_profiler_gmalloc_amd64Xmemory='Only 4 memory samples were recorded;at least 5 are needed' \
           INCONCLUSIVE_profiler_tracer_jemalloc_aarch64Xmemory='PSI cpu median above the bound'
assert_exit "an inconclusive-only run exits 0" 0
assert_body_contains "an inconclusive-only run gets the inconclusive headline" \
  "⚠️ **2 memory check row(s) inconclusive — no failures**"
assert_body_contains "the first inconclusive row gets a warning details block" \
  "<details><summary>⚠️ profiler gmalloc amd64Xmemory</summary>"
assert_body_contains "the second inconclusive row gets a warning details block" \
  "<details><summary>⚠️ profiler tracer jemalloc aarch64Xmemory</summary>"
assert_body_contains "the inconclusive reason text is kept in the block" \
  "Only 4 memory samples were recorded"
assert_body_lacks "an inconclusive-only run never shows the success headline" \
  "All reliability & chaos checks passed"
assert_body_lacks "an inconclusive-only run reports no failure headline" \
  "failure(s) detected"

# --- REASON_* failures plus inconclusive rows ---------------------------------

run_script REASON_profiler_gmalloc_amd64Xjit='jit crash' \
           INCONCLUSIVE_profiler_gmalloc_amd64Xmemory='PSI cpu median above the bound'
assert_exit "a run with both kinds exits 0" 0
assert_body_contains "the failure headline still leads" \
  "❌ **1 failure(s) detected** · ⚠️ 1 inconclusive row(s)"
assert_body_contains "the failure details block is still rendered" \
  "<details><summary>❌ profiler gmalloc amd64Xjit</summary>"
assert_body_contains "the inconclusive details block is rendered alongside" \
  "<details><summary>⚠️ profiler gmalloc amd64Xmemory</summary>"

# --- neither failures nor inconclusive rows -----------------------------------

run_script CI_PIPELINE_URL='https://x/pipeline/2'
assert_exit "a green run exits 0" 0
assert_body_contains "a green run keeps the success headline" \
  "✅ **All reliability & chaos checks passed**"
assert_body_lacks "a green run renders no details block" "<details>"

# --- only INCONCLUSIVE keys for other variants are not inconclusive rows ------

run_script INCONCLUSIVE_profiler_gmalloc_amd64Xjit='whatever' \
           INCONCLUSIVE_profiler_gmalloc_aarch64Xchaos='whatever'
assert_exit "non-memory INCONCLUSIVE keys alone exit 0" 0
assert_body_contains "non-memory INCONCLUSIVE keys render no warning row" \
  "✅ **All reliability & chaos checks passed**"
assert_body_lacks "non-memory INCONCLUSIVE keys render no details block" "<details>"

# --- the capture seam and the unchanged production posting -------------------

# The replica runs the byte-identical script in a tree whose upsert is a stub
# that records its arguments, so the posting path runs without network access.
REPLICA="${WORK}/replica"
mkdir -p "${REPLICA}/scripts" "${REPLICA}/reliability"
cp "${SCRIPT}" "${REPLICA}/reliability/post-pr-comment.sh"
cat > "${REPLICA}/scripts/upsert-github-pr-comment.sh" <<'STUB'
#!/usr/bin/env bash
printf 'ARGS:%s|%s\n' "$1" "$2" > "${UPSERT_CAPTURE_DIR}/upsert.args"
cp "$3" "${UPSERT_CAPTURE_DIR}/posted.body"
STUB
chmod +x "${REPLICA}/scripts/upsert-github-pr-comment.sh"

if cmp -s "${SCRIPT}" "${REPLICA}/reliability/post-pr-comment.sh"; then
  pass "the replica runs the script under test byte-for-byte"
else
  fail_case "the replica differs from the script under test"
fi

# Production posting: the seam is unset, so the upsert must be called with the
# same arguments as before the change.
: > "${REPLICA}/upsert.args"
SCRIPT_EXIT=0
UPSERT_CAPTURE_DIR="${REPLICA}" REASON_profiler_gmalloc_amd64Xjit='jit crash' \
  DDPROF_COMMIT_BRANCH=pr-branch bash "${REPLICA}/reliability/post-pr-comment.sh" \
  >"${WORK}/log.txt" 2>&1 || SCRIPT_EXIT=$?
assert_exit "posting runs without the capture seam, exit 0" 0
if [ "$(cat "${REPLICA}/upsert.args")" = "ARGS:reliability-results|pr-branch" ]; then
  pass "the upsert is called with the same comment id and branch as before"
else
  fail_case "the upsert arguments changed: $(cat "${REPLICA}/upsert.args")"
fi
if grep -qF '❌ **1 failure(s) detected**' "${REPLICA}/posted.body"; then
  pass "the posted body is the rendered comment"
else
  fail_case "the posted body is not the rendered comment"
fi

# Capture seam: with COMMENT_BODY_FILE set the body is captured and nothing is
# posted, which is what keeps these tests network-free.
rm -f "${REPLICA}/upsert.args" "${REPLICA}/posted.body"
SCRIPT_EXIT=0
UPSERT_CAPTURE_DIR="${REPLICA}" COMMENT_BODY_FILE="${BODY}" \
  REASON_profiler_gmalloc_amd64Xjit='jit crash' \
  DDPROF_COMMIT_BRANCH=pr-branch bash "${REPLICA}/reliability/post-pr-comment.sh" \
  >"${WORK}/log.txt" 2>&1 || SCRIPT_EXIT=$?
assert_exit "capture-seam posting skip exits 0" 0
if [ ! -e "${REPLICA}/upsert.args" ]; then
  pass "the capture seam posts nothing"
else
  fail_case "the capture seam still invoked the upsert"
fi

if [ "${FAILED}" -eq 0 ]; then
  echo "All post_pr_comment tests passed"
  exit 0
fi
echo "post_pr_comment tests failed"
exit 1
