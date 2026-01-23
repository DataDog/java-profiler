#!/bin/bash
# Track upstream async-profiler changes and generate reports

set -e

show_help() {
    cat <<EOF
Usage: $(basename "$0") [OPTIONS] REPO_PATH LAST_COMMIT CURRENT_COMMIT FILES_LIST MD_OUT JSON_OUT

Core change detection and report generation for upstream tracking.

ARGUMENTS:
    REPO_PATH           Path to cloned upstream repository
    LAST_COMMIT         Baseline commit SHA/tag to compare from
    CURRENT_COMMIT      Current commit SHA to compare to
    FILES_LIST          Path to file containing tracked files (one per line)
    MD_OUT              Path for markdown report output
    JSON_OUT            Path for JSON report output

OPTIONS:
    -h, --help          Show this help message and exit

DESCRIPTION:
    Analyzes changes between two commits in the upstream repository for a set
    of tracked files. Generates comprehensive reports including:
    - List of changed files with commit counts
    - Detailed commit messages (up to 20 per file)
    - Referenced pull requests
    - Links to GitHub compare views

    If no changes are detected, exits without creating report files.

OUTPUT FILES:
    Markdown report:
        - Human-readable format
        - Grouped by file with commit details
        - Sorted by number of commits (descending)
        - Includes action items and resource links

    JSON report:
        - Machine-readable format
        - Structured data for automation
        - Used by Slack notifications

EXAMPLES:
    # Basic usage
    $(basename "$0") /tmp/async-profiler v4.2.1 abc1234 files.txt report.md report.json

    # With full commit SHAs
    $(basename "$0") /tmp/async-profiler \\
        7d5d747be160e280 \\
        a071e8a2f8cf8be4 \\
        tracked.txt \\
        changes.md \\
        changes.json

EXIT STATUS:
    0    Success (reports generated or no changes detected)
    1    Error (invalid arguments, git command failures, etc.)

NOTES:
    - Commits are limited to 20 per file to keep reports manageable
    - PR numbers are extracted from commit messages in format: (#1234)
    - Requires git to be available in PATH

EOF
}

# Parse arguments
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    show_help
    exit 0
fi

UPSTREAM_REPO="$1"
LAST_COMMIT="$2"
CURRENT_COMMIT="$3"
TRACKED_FILES="$4"
OUTPUT_MD="$5"
OUTPUT_JSON="$6"

cd "$UPSTREAM_REPO"

# Check if there are any changes
if [ "$LAST_COMMIT" = "$CURRENT_COMMIT" ]; then
    echo "No changes detected (commits match)"
    exit 0
fi

# Get all commits as a single string
ALL_COMMITS=$(git log --oneline "$LAST_COMMIT..$CURRENT_COMMIT" 2>/dev/null)

if [ -z "$ALL_COMMITS" ]; then
    echo "No new commits found"
    exit 0
fi

# Count total commits
TOTAL_COMMITS=$(echo "$ALL_COMMITS" | wc -l | tr -d ' ')

# Extract PR numbers from commit messages
extract_pr_numbers() {
    local commits="$1"
    echo "$commits" | grep -o '(#[0-9]\+)' | sed 's/(#\([0-9]*\))/\1/' | sort -u || true
}

# Get list of commits for display (limited to 20)
COMMITS_DISPLAY=$(echo "$ALL_COMMITS" | head -20)
if [ $TOTAL_COMMITS -gt 20 ]; then
    COMMITS_DISPLAY="${COMMITS_DISPLAY}
... and $((TOTAL_COMMITS - 20)) more commits"
fi

# Extract all PR numbers
PR_NUMBERS=$(extract_pr_numbers "$ALL_COMMITS")

# Generate short commit range for display
SHORT_LAST=$(echo "$LAST_COMMIT" | cut -c1-7)
SHORT_CURRENT=$(echo "$CURRENT_COMMIT" | cut -c1-7)
COMMIT_RANGE="${SHORT_LAST}...${SHORT_CURRENT}"

# Track which files were modified - use temp directory for per-file data
TEMP_DATA_DIR="$(mktemp -d)"
trap "rm -rf $TEMP_DATA_DIR" EXIT

changed_files_list=()
changed_files_count=0

# For each tracked file, check if it was modified
while IFS= read -r file; do
    if [ -z "$file" ]; then
        continue
    fi

    # Check if file was modified in commit range
    if git diff --quiet "$LAST_COMMIT" "$CURRENT_COMMIT" -- "$file" 2>/dev/null; then
        continue  # No changes to this file
    fi

    # Get commit list for this file (limited to 20)
    commits_for_file=$(git log --oneline "$LAST_COMMIT..$CURRENT_COMMIT" -- "$file" | head -20)
    commit_count=$(echo "$commits_for_file" | wc -l | tr -d ' ')

    # Store commits in a file, and track file:count
    file_id=$(printf "%03d" $changed_files_count)
    echo "$commits_for_file" > "$TEMP_DATA_DIR/${file_id}.commits"
    echo "$file" > "$TEMP_DATA_DIR/${file_id}.path"
    echo "$commit_count" > "$TEMP_DATA_DIR/${file_id}.count"

    changed_files_list+=("$file_id:$commit_count")
    changed_files_count=$((changed_files_count + 1))
done < "$TRACKED_FILES"

if [ $changed_files_count -eq 0 ]; then
    echo "No changes to tracked files"
    exit 0
fi

# Sort file IDs by commit count (descending)
SORTED_FILE_IDS=$(printf '%s\n' "${changed_files_list[@]}" | sort -t':' -k2 -rn | cut -d':' -f1)

# Generate Markdown Report
cat > "$OUTPUT_MD" <<EOF
# Upstream async-profiler Changes Detected

**Date**: $(date +%Y-%m-%d)
**Commit Range**: [\`${COMMIT_RANGE}\`](https://github.com/async-profiler/async-profiler/compare/${LAST_COMMIT}...${CURRENT_COMMIT})
**Files Changed**: ${changed_files_count}
**Total Commits**: ${TOTAL_COMMITS}

## Summary

${changed_files_count} files in \`ddprof-lib/src/main/cpp\` have corresponding changes in upstream async-profiler.

## Changed Files

EOF

# Process each changed file for markdown
echo "$SORTED_FILE_IDS" | while read -r file_id; do
    file=$(cat "$TEMP_DATA_DIR/${file_id}.path")
    count=$(cat "$TEMP_DATA_DIR/${file_id}.count")
    basename_file=$(basename "$file")

    cat >> "$OUTPUT_MD" <<EOF
### ${basename_file}
**Commits**: ${count}

EOF

    # Show first 5 commits
    head -5 "$TEMP_DATA_DIR/${file_id}.commits" | while read -r commit_line; do
        echo "- ${commit_line}" >> "$OUTPUT_MD"
    done

    commit_count_for_file=$(wc -l < "$TEMP_DATA_DIR/${file_id}.commits" | tr -d ' ')
    if [ "$commit_count_for_file" -gt 5 ]; then
        echo "- ... and $((commit_count_for_file - 5)) more commits" >> "$OUTPUT_MD"
    fi

    echo "" >> "$OUTPUT_MD"
    echo "**View diff**: [${basename_file}](https://github.com/async-profiler/async-profiler/commits/${CURRENT_COMMIT}/${file})" >> "$OUTPUT_MD"
    echo "" >> "$OUTPUT_MD"
done

# Add recent commits section
cat >> "$OUTPUT_MD" <<EOF
## Recent Commits

EOF

echo "$COMMITS_DISPLAY" | while read -r commit_line; do
    echo "- ${commit_line}" >> "$OUTPUT_MD"
done

# Add PR references if any
if [ -n "$PR_NUMBERS" ]; then
    cat >> "$OUTPUT_MD" <<EOF

## Referenced Pull Requests

EOF

    echo "$PR_NUMBERS" | while read -r pr_num; do
        echo "- [#${pr_num}](https://github.com/async-profiler/async-profiler/pull/${pr_num})" >> "$OUTPUT_MD"
    done
fi

# Add action items
cat >> "$OUTPUT_MD" <<EOF

## Action Items

1. Review changed files for compatibility with Datadog modifications
2. Test changes in Datadog profiler context
3. Update integration if necessary
4. Consider upstreaming any Datadog-specific fixes if applicable

## Resources

- [Upstream compare view](https://github.com/async-profiler/async-profiler/compare/${LAST_COMMIT}...${CURRENT_COMMIT})
- [Async-profiler repository](https://github.com/async-profiler/async-profiler)
EOF

# Generate JSON Report
cat > "$OUTPUT_JSON" <<EOF
{
  "date": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
  "last_commit": "${LAST_COMMIT}",
  "current_commit": "${CURRENT_COMMIT}",
  "commit_range": "${COMMIT_RANGE}",
  "files_changed": ${changed_files_count},
  "commit_count": ${TOTAL_COMMITS},
  "summary": "${changed_files_count} files changed in upstream async-profiler (${TOTAL_COMMITS} commits)",
  "files": [
EOF

# Add file details to JSON
file_index=0
for file_id in $SORTED_FILE_IDS; do
    file=$(cat "$TEMP_DATA_DIR/${file_id}.path")
    count=$(cat "$TEMP_DATA_DIR/${file_id}.count")
    basename_file=$(basename "$file")

    if [ $file_index -gt 0 ]; then
        echo "," >> "$OUTPUT_JSON"
    fi

    cat >> "$OUTPUT_JSON" <<EOF
    {
      "path": "${basename_file}",
      "commit_count": ${count}
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
