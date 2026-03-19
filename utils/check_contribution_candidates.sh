#!/bin/bash
# Check divergences from upstream async-profiler for potential contributions

set -e

show_help() {
    cat <<EOF
Usage: $(basename "$0") [OPTIONS] [BASELINE]

Identify divergences from upstream async-profiler that could be contributed back.

ARGUMENTS:
    BASELINE            Baseline tag/commit in upstream to compare against (default: v4.2.1)

OPTIONS:
    -h, --help          Show this help message and exit

DESCRIPTION:
    This script clones the upstream async-profiler repository and, for each tracked
    file, diffs the upstream version (at the baseline tag) against our repo version.
    Hunks are classified as Datadog-specific or potential contribution candidates.

    Tracked files are those in ddprof-lib/src/main/cpp that:
    - Contain async-profiler copyright headers
    - Have corresponding files in upstream async-profiler

OUTPUT:
    Reports are saved to: build/contribution-reports/
    - contribution_candidates_YYYYMMDD_HHMMSS.md  (human-readable)
    - contribution_candidates_YYYYMMDD_HHMMSS.json (machine-readable)
    - tracked_files.txt (list of tracked files)

EXAMPLES:
    # Compare against upstream v4.2.1 (default baseline)
    $(basename "$0")

    # Compare against a different baseline
    $(basename "$0") v3.0

EXIT STATUS:
    0    Success (with or without candidates detected)
    1    Error (clone failed, invalid arguments, etc.)

EOF
}

# Parse arguments
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    show_help
    exit 0
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# Configuration
UPSTREAM_REPO_URL="https://github.com/async-profiler/async-profiler.git"
TMPDIR="${TMPDIR:-/tmp}"
UPSTREAM_CLONE_DIR="$(mktemp -d "$TMPDIR/async-profiler-contrib.XXXXXX")"
LOCAL_CPP_DIR="$PROJECT_ROOT/ddprof-lib/src/main/cpp"
REPORT_DIR="$PROJECT_ROOT/build/contribution-reports"

BASELINE="${1:-v4.2.1}"

echo "=== Contribution Candidate Checker ==="
echo ""
echo "Configuration:"
echo "  Local cpp dir: $LOCAL_CPP_DIR"
echo "  Baseline: $BASELINE"
echo "  Report dir: $REPORT_DIR"
echo ""

# Create report directory
mkdir -p "$REPORT_DIR"

# Clone upstream repository
echo "[1/4] Cloning upstream async-profiler..."
git clone -q --depth 200 "$UPSTREAM_REPO_URL" "$UPSTREAM_CLONE_DIR"
cd "$UPSTREAM_CLONE_DIR"
git fetch -q --tags
echo "  Cloned to $UPSTREAM_CLONE_DIR"
echo ""

# Generate tracked files list
echo "[2/4] Discovering tracked files..."
TRACKED_FILES="$REPORT_DIR/tracked_files.txt"
"$SCRIPT_DIR/generate_tracked_files.sh" \
    "$LOCAL_CPP_DIR" \
    "$UPSTREAM_CLONE_DIR/src" \
    > "$TRACKED_FILES"

FILE_COUNT=$(wc -l < "$TRACKED_FILES" | tr -d ' ')
echo "  Tracking $FILE_COUNT files"
echo ""

# Analyze contribution candidates
echo "[3/4] Analyzing divergences from upstream..."
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
MARKDOWN_REPORT="$REPORT_DIR/contribution_candidates_${TIMESTAMP}.md"
JSON_REPORT="$REPORT_DIR/contribution_candidates_${TIMESTAMP}.json"

"$SCRIPT_DIR/find_contribution_candidates.sh" \
    "$UPSTREAM_CLONE_DIR" \
    "$BASELINE" \
    "$LOCAL_CPP_DIR" \
    "$TRACKED_FILES" \
    "$MARKDOWN_REPORT" \
    "$JSON_REPORT"

# Check results
if [ ! -f "$JSON_REPORT" ]; then
    echo "  No contribution candidates detected."
    echo ""
    echo "All divergences are Datadog-specific."
else
    CANDIDATES=$(jq -r '.files_with_candidates' "$JSON_REPORT")
    TOTAL_CHANGED=$(jq -r '.files_with_changes' "$JSON_REPORT")

    echo ""
    echo "  Candidates found!"
    echo "    Files with divergences: $TOTAL_CHANGED"
    echo "    Files with contributable hunks: $CANDIDATES"
    echo ""
    echo "Reports generated:"
    echo "  Markdown: $MARKDOWN_REPORT"
    echo "  JSON: $JSON_REPORT"
    echo ""
    echo "View the markdown report:"
    echo "  cat $MARKDOWN_REPORT"
fi

# Cleanup
echo ""
echo "[4/4] Cleaning up..."
rm -rf "$UPSTREAM_CLONE_DIR"
echo "  Removed temporary clone"

echo ""
echo "Done!"
echo ""
echo "Tracked files list saved to:"
echo "  $TRACKED_FILES"
