#!/usr/bin/env bash
# Post aggregated reliability + chaos test results as a single PR comment.
#
# Reads REASON_* and INCONCLUSIVE_* variables written to build.env by the
# reliability/chaos jobs and emits a ✅/❌/⚠️ matrix with failure and
# inconclusive <details> blocks. Inconclusive rows never fail the pipeline.
#
# Required env:
#   DDPROF_COMMIT_BRANCH  – branch name used to locate the open PR
# Optional env:
#   CI_PIPELINE_URL
#   COMMENT_BODY_FILE     – capture seam: write the body here instead of posting

set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# ── Collect failures from REASON_* env vars ────────────────────────────────────
rel_fail=0; rel_failures=""
chaos_fail=0; chaos_failures=""
inconclusive=0; inconclusive_details=""

for key in $(compgen -v | grep -E '^REASON_.*X(jit|memory)$' | sort); do
  reason="${!key}"
  label="${key#REASON_}"
  rel_fail=$((rel_fail + 1))
  detail=$(printf '%s' "${reason//\`/}" | tr ';' '\n')
  rel_failures="${rel_failures}
<details><summary>❌ ${label//_/ }</summary>

\`\`\`
${detail}
\`\`\`

</details>"
done

for key in $(compgen -v | grep -E '^REASON_.*Xchaos$' | sort); do
  reason="${!key}"
  label="${key#REASON_}"
  chaos_fail=$((chaos_fail + 1))
  detail=$(printf '%s' "${reason//\`/}" | tr ';' '\n')
  chaos_failures="${chaos_failures}
<details><summary>❌ chaos: ${label//_/ }</summary>

\`\`\`
${detail}
\`\`\`

</details>"
done

# ── Collect inconclusive memory rows from INCONCLUSIVE_* env vars ───────────────

for key in $(compgen -v | grep -E '^INCONCLUSIVE_.*Xmemory$' | sort); do
  reason="${!key}"
  label="${key#INCONCLUSIVE_}"
  inconclusive=$((inconclusive + 1))
  detail=$(printf '%s' "${reason//\`/}" | tr ';' '\n')
  inconclusive_details="${inconclusive_details}
<details><summary>⚠️ ${label//_/ }</summary>

\`\`\`
${detail}
\`\`\`

</details>"
done

# ── Assemble comment ────────────────────────────────────────────────────────────
total_fail=$((rel_fail + chaos_fail))
if [ "${total_fail}" -gt 0 ]; then
  overall="❌ **${total_fail} failure(s) detected**"
  if [ "${inconclusive}" -gt 0 ]; then
    overall="${overall} · ⚠️ ${inconclusive} inconclusive row(s)"
  fi
elif [ "${inconclusive}" -gt 0 ]; then
  overall="⚠️ **${inconclusive} memory check row(s) inconclusive — no failures**"
else
  overall="✅ **All reliability & chaos checks passed**"
fi

# COMMENT_BODY_FILE lets a test capture the rendered body; production posting
# is unchanged whenever it is unset.
if [ -n "${COMMENT_BODY_FILE:-}" ]; then
  BODY_FILE="${COMMENT_BODY_FILE}"
else
  BODY_FILE=$(mktemp)
  trap 'rm -f "${BODY_FILE}"' EXIT
fi
cat > "${BODY_FILE}" <<EOF
## Reliability & Chaos Results

${overall}  Pipeline: ${CI_PIPELINE_URL:-}
${rel_failures}${chaos_failures}${inconclusive_details}
EOF

if [ -z "${COMMENT_BODY_FILE:-}" ]; then
  "${HERE}/../scripts/upsert-github-pr-comment.sh" \
    "reliability-results" "${DDPROF_COMMIT_BRANCH:-}" "${BODY_FILE}"
fi
