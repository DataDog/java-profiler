#!/bin/bash
# Analyze divergences from upstream async-profiler and identify contribution candidates

set -e

show_help() {
    cat <<EOF
Usage: $(basename "$0") [OPTIONS] UPSTREAM_REPO BASELINE_COMMIT LOCAL_CPP_DIR FILES_LIST MD_OUT JSON_OUT

Core diff analysis and report generation for contribution candidate detection.

ARGUMENTS:
    UPSTREAM_REPO       Path to cloned upstream repository
    BASELINE_COMMIT     Baseline commit/tag in upstream to compare against
    LOCAL_CPP_DIR       Path to local ddprof-lib/src/main/cpp directory
    FILES_LIST          Path to file containing tracked files (one per line)
    MD_OUT              Path for markdown report output
    JSON_OUT            Path for JSON report output

OPTIONS:
    -h, --help          Show this help message and exit

DESCRIPTION:
    For each tracked file, diffs the upstream version (at baseline) against our
    repo version, then classifies each hunk as either Datadog-specific or a
    potential contribution candidate.

    Datadog-specific hunks contain markers such as DD_, ddprof, Datadog,
    datadog, DDPROF, context.h, counters.h, tagger, or QueueItem.

    Hunks without these markers are flagged as potential contributions.

OUTPUT FILES:
    Markdown report:
        - Summary of candidate files sorted by contributable hunk count
        - Preview of contributable diff hunks
        - Action items

    JSON report:
        - Machine-readable structured data

EXIT STATUS:
    0    Success (reports generated or no candidates detected)
    1    Error (invalid arguments, etc.)

EOF
}

# Parse arguments
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    show_help
    exit 0
fi

UPSTREAM_REPO="$1"
BASELINE_COMMIT="$2"
LOCAL_CPP_DIR="$3"
TRACKED_FILES="$4"
OUTPUT_MD="$5"
OUTPUT_JSON="$6"

if [ -z "$OUTPUT_JSON" ]; then
    echo "Error: missing required arguments" >&2
    show_help >&2
    exit 1
fi

# DD-specific markers used to classify hunks
DD_MARKERS='DD_\|ddprof\|Datadog\|datadog\|DDPROF\|context\.h\|counters\.h\|tagger\|QueueItem'

TEMP_DATA_DIR="$(mktemp -d)"
trap "rm -rf $TEMP_DATA_DIR" EXIT

candidate_count=0
total_with_changes=0

while IFS= read -r file; do
    if [ -z "$file" ]; then
        continue
    fi

    basename_file=$(basename "$file")

    # Extract upstream version at baseline
    upstream_content=$(cd "$UPSTREAM_REPO" && git show "${BASELINE_COMMIT}:${file}" 2>/dev/null) || continue
    local_file="$LOCAL_CPP_DIR/$basename_file"

    if [ ! -f "$local_file" ]; then
        continue
    fi

    # Write upstream content to temp file for diffing
    echo "$upstream_content" > "$TEMP_DATA_DIR/upstream_${basename_file}"

    # Diff upstream (baseline) vs local; non-zero exit means differences exist
    diff_output=$(diff -u "$TEMP_DATA_DIR/upstream_${basename_file}" "$local_file" 2>/dev/null) || true

    if [ -z "$diff_output" ]; then
        continue
    fi

    total_with_changes=$((total_with_changes + 1))

    # Split diff into hunks and classify each using awk (fast single-pass)
    echo "$diff_output" > "$TEMP_DATA_DIR/full_diff_${basename_file}"

    # awk splits on @@ lines, classifies each hunk by DD markers, writes
    # contrib hunks to contrib_file, and prints "contrib_count dd_count" at end
    read -r contrib_hunks dd_hunks <<< "$(awk -v contrib_file="$TEMP_DATA_DIR/contrib_hunks_${basename_file}" \
        -v dd_pat='DD_|ddprof|Datadog|datadog|DDPROF|context\\.h|counters\\.h|tagger|QueueItem' \
    '
    BEGIN { in_hunk = 0; contrib = 0; dd = 0; hunk = "" ; is_dd = 0 }
    /^@@/ {
        if (in_hunk) {
            if (is_dd) { dd++ }
            else { contrib++; printf "%s\n---HUNK_BOUNDARY---\n", hunk >> contrib_file }
        }
        hunk = $0; is_dd = 0; in_hunk = 1; next
    }
    /^---( |$)/ && !in_hunk { next }
    /^\+\+\+( |$)/ && !in_hunk { next }
    in_hunk {
        hunk = hunk "\n" $0
        if ($0 ~ dd_pat) is_dd = 1
    }
    END {
        if (in_hunk) {
            if (is_dd) { dd++ }
            else { contrib++; printf "%s\n---HUNK_BOUNDARY---\n", hunk >> contrib_file }
        }
        print contrib, dd
    }
    ' "$TEMP_DATA_DIR/full_diff_${basename_file}")"

    total_hunks=$((contrib_hunks + dd_hunks))

    if [ $contrib_hunks -gt 0 ]; then
        file_id=$(printf "%03d" $candidate_count)
        echo "$basename_file" > "$TEMP_DATA_DIR/${file_id}.path"
        echo "$contrib_hunks" > "$TEMP_DATA_DIR/${file_id}.contrib"
        echo "$dd_hunks" > "$TEMP_DATA_DIR/${file_id}.dd"
        echo "$total_hunks" > "$TEMP_DATA_DIR/${file_id}.total"
        cp "$TEMP_DATA_DIR/contrib_hunks_${basename_file}" "$TEMP_DATA_DIR/${file_id}.hunks" 2>/dev/null || true

        candidate_count=$((candidate_count + 1))
    fi
done < "$TRACKED_FILES"

if [ $candidate_count -eq 0 ]; then
    echo "No contribution candidates detected"
    exit 0
fi

# Build sorted index (by contrib hunk count, descending)
sorted_ids=""
for i in $(seq 0 $((candidate_count - 1))); do
    file_id=$(printf "%03d" $i)
    contrib=$(cat "$TEMP_DATA_DIR/${file_id}.contrib")
    sorted_ids="${sorted_ids}${file_id}:${contrib}
"
done
SORTED_FILE_IDS=$(echo "$sorted_ids" | grep -v '^$' | sort -t':' -k2 -rn | cut -d':' -f1)

# --- Markdown Report ---
cat > "$OUTPUT_MD" <<EOF
# Contribution Candidates for async-profiler

**Date**: $(date +%Y-%m-%d)
**Baseline Tag**: ${BASELINE_COMMIT}
**Files with Divergences**: ${total_with_changes}
**Files with Contributable Hunks**: ${candidate_count}

## Summary

${candidate_count} of ${total_with_changes} divergent files have hunks that may be contributable to upstream async-profiler.

## Candidates

EOF

echo "$SORTED_FILE_IDS" | while read -r file_id; do
    [ -z "$file_id" ] && continue
    fname=$(cat "$TEMP_DATA_DIR/${file_id}.path")
    contrib=$(cat "$TEMP_DATA_DIR/${file_id}.contrib")
    dd=$(cat "$TEMP_DATA_DIR/${file_id}.dd")
    total=$(cat "$TEMP_DATA_DIR/${file_id}.total")

    cat >> "$OUTPUT_MD" <<EOF
### ${fname}
- **Total hunks**: ${total} (${contrib} contributable, ${dd} Datadog-specific)

EOF

    # Show preview of contributable hunks (first 15 lines per hunk, up to 3 hunks)
    if [ -f "$TEMP_DATA_DIR/${file_id}.hunks" ]; then
        echo '```diff' >> "$OUTPUT_MD"
        hunk_shown=0
        while IFS= read -r line; do
            if [ "$line" = "---HUNK_BOUNDARY---" ]; then
                hunk_shown=$((hunk_shown + 1))
                if [ $hunk_shown -ge 3 ]; then
                    break
                fi
                echo "" >> "$OUTPUT_MD"
                continue
            fi
            echo "$line" >> "$OUTPUT_MD"
        done < "$TEMP_DATA_DIR/${file_id}.hunks"
        echo '```' >> "$OUTPUT_MD"
        if [ $contrib -gt 3 ]; then
            echo "_... and $((contrib - 3)) more contributable hunks_" >> "$OUTPUT_MD"
        fi
        echo "" >> "$OUTPUT_MD"
    fi
done

cat >> "$OUTPUT_MD" <<EOF
## Action Items

1. Review each candidate diff for upstream applicability
2. Extract contributable changes into standalone patches
3. Submit PRs to async-profiler

## Resources

- [async-profiler repository](https://github.com/async-profiler/async-profiler)
- [Baseline tag: ${BASELINE_COMMIT}](https://github.com/async-profiler/async-profiler/tree/${BASELINE_COMMIT})
EOF

# --- JSON Report ---
cat > "$OUTPUT_JSON" <<EOF
{
  "date": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "baseline_commit": "${BASELINE_COMMIT}",
  "files_with_changes": ${total_with_changes},
  "files_with_candidates": ${candidate_count},
  "files": [
EOF

file_index=0
for file_id in $SORTED_FILE_IDS; do
    [ -z "$file_id" ] && continue
    fname=$(cat "$TEMP_DATA_DIR/${file_id}.path")
    contrib=$(cat "$TEMP_DATA_DIR/${file_id}.contrib")
    dd=$(cat "$TEMP_DATA_DIR/${file_id}.dd")
    total=$(cat "$TEMP_DATA_DIR/${file_id}.total")

    if [ $file_index -gt 0 ]; then
        echo "," >> "$OUTPUT_JSON"
    fi

    cat >> "$OUTPUT_JSON" <<EOF
    {
      "path": "${fname}",
      "total_hunks": ${total},
      "contributable_hunks": ${contrib},
      "dd_specific_hunks": ${dd}
    }
EOF
    file_index=$((file_index + 1))
done

cat >> "$OUTPUT_JSON" <<EOF

  ]
}
EOF

echo "Reports generated successfully"
echo "  Markdown: $OUTPUT_MD"
echo "  JSON: $OUTPUT_JSON"
