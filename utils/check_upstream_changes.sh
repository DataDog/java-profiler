#!/bin/bash
# Convenient wrapper to check upstream async-profiler changes locally

set -e

show_help() {
    cat <<EOF
Usage: $(basename "$0") [OPTIONS] [COMMIT]

Check for changes in upstream async-profiler repository compared to a baseline commit.

ARGUMENTS:
    COMMIT              Baseline commit to compare against (default: v4.2.1)
                        Can be a commit SHA, tag, or relative reference like HEAD~10

OPTIONS:
    -h, --help          Show this help message and exit

DESCRIPTION:
    This script clones the upstream async-profiler repository and compares tracked
    files against a baseline commit. It generates markdown and JSON reports showing
    which files have changed and the nature of those changes.

    Tracked files are those in ddprof-lib/src/main/cpp that:
    - Contain async-profiler copyright headers
    - Have corresponding files in upstream async-profiler

OUTPUT:
    Reports are saved to: build/upstream-reports/
    - upstream_changes_YYYYMMDD_HHMMSS.md  (human-readable)
    - upstream_changes_YYYYMMDD_HHMMSS.json (machine-readable)
    - tracked_files.txt (list of tracked files)

EXAMPLES:
    # Compare against v4.2.1 (current baseline)
    $(basename "$0")

    # Compare against specific commit
    $(basename "$0") abc1234

    # Compare against 10 commits ago
    $(basename "$0") HEAD~10

    # Compare against latest v3.x tag
    $(basename "$0") v3.0

EXIT STATUS:
    0    Success (with or without changes detected)
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
UPSTREAM_CLONE_DIR="$(mktemp -d "$TMPDIR/async-profiler-check.XXXXXX")"
LOCAL_CPP_DIR="$PROJECT_ROOT/ddprof-lib/src/main/cpp"
REPORT_DIR="$PROJECT_ROOT/build/upstream-reports"

# Default to v4.2.1 if no commit provided
LAST_COMMIT="${1:-v4.2.1}"

echo "=== Upstream async-profiler Change Checker ==="
echo ""
echo "Configuration:"
echo "  Local cpp dir: $LOCAL_CPP_DIR"
echo "  Comparing against: $LAST_COMMIT"
echo "  Report dir: $REPORT_DIR"
echo ""

# Create report directory
mkdir -p "$REPORT_DIR"

# Clone upstream repository
echo "[1/5] Cloning upstream async-profiler..."
# Clone with sufficient depth to include tags/old commits
git clone -q --depth 200 "$UPSTREAM_REPO_URL" "$UPSTREAM_CLONE_DIR"
cd "$UPSTREAM_CLONE_DIR"

git fetch -q origin master
git fetch -q --tags

CURRENT_HEAD=$(git rev-parse origin/master)

echo "  Upstream HEAD: $CURRENT_HEAD"
echo ""

# Generate tracked files list
echo "[2/5] Discovering tracked files..."
TRACKED_FILES="$REPORT_DIR/tracked_files.txt"
"$SCRIPT_DIR/generate_tracked_files.sh" \
    "$LOCAL_CPP_DIR" \
    "$UPSTREAM_CLONE_DIR/src" \
    > "$TRACKED_FILES"

FILE_COUNT=$(wc -l < "$TRACKED_FILES" | tr -d ' ')
echo "  Tracking $FILE_COUNT files"
echo ""

# Check for changes
echo "[3/5] Analyzing changes..."
MARKDOWN_REPORT="$REPORT_DIR/upstream_changes_$(date +%Y%m%d_%H%M%S).md"
JSON_REPORT="$REPORT_DIR/upstream_changes_$(date +%Y%m%d_%H%M%S).json"

"$SCRIPT_DIR/track_upstream_changes.sh" \
    "$UPSTREAM_CLONE_DIR" \
    "$LAST_COMMIT" \
    "$CURRENT_HEAD" \
    "$TRACKED_FILES" \
    "$MARKDOWN_REPORT" \
    "$JSON_REPORT"

# Check if reports were generated
if [ ! -f "$JSON_REPORT" ]; then
    echo "  No changes detected!"
    echo ""
    echo "✓ All tracked files are up to date with upstream."
else
    FILES_CHANGED=$(jq -r '.files_changed' "$JSON_REPORT")
    COMMIT_COUNT=$(jq -r '.commit_count' "$JSON_REPORT")

    echo "  Changes detected!"
    echo "    Files changed: $FILES_CHANGED"
    echo "    Commits: $COMMIT_COUNT"
    echo ""
    echo "✓ Reports generated:"
    echo "    Markdown: $MARKDOWN_REPORT"
    echo "    JSON: $JSON_REPORT"
    echo ""
    echo "View the markdown report:"
    echo "  cat $MARKDOWN_REPORT"
fi

# Cleanup
echo ""
echo "[4/5] Cleaning up..."
rm -rf "$UPSTREAM_CLONE_DIR"
echo "  Removed temporary clone"

echo ""
echo "[5/5] Done!"
echo ""
echo "Tracked files list saved to:"
echo "  $TRACKED_FILES"
