#!/bin/bash
# Generate list of files to track from upstream async-profiler

set -e

show_help() {
    cat <<EOF
Usage: $(basename "$0") [OPTIONS] LOCAL_DIR UPSTREAM_DIR

Identify which local C++ files should be tracked against upstream async-profiler.

ARGUMENTS:
    LOCAL_DIR           Path to local cpp directory (e.g., ddprof-lib/src/main/cpp)
    UPSTREAM_DIR        Path to upstream src directory (e.g., /tmp/async-profiler/src)

OPTIONS:
    -h, --help          Show this help message and exit

DESCRIPTION:
    Scans the local C++ directory and identifies files that originated from
    async-profiler by checking:
    1. File contains "Copyright.*async-profiler authors" in its content
    2. Corresponding file exists in the upstream repository

    Output is a list of relative paths (e.g., src/profiler.cpp) that should
    be tracked for upstream changes.

OUTPUT:
    One file path per line, relative to upstream repo root:
        src/profiler.cpp
        src/stackWalker.cpp
        ...

EXAMPLES:
    # Standard usage
    $(basename "$0") ddprof-lib/src/main/cpp /tmp/async-profiler/src

    # Save to file
    $(basename "$0") ddprof-lib/src/main/cpp /tmp/async-profiler/src > tracked.txt

    # Count tracked files
    $(basename "$0") ddprof-lib/src/main/cpp /tmp/async-profiler/src | wc -l

EXIT STATUS:
    0    Success (tracked files listed)
    1    Error (missing directories, etc.)

EOF
}

# Parse arguments
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    show_help
    exit 0
fi

LOCAL_DIR="$1"
UPSTREAM_DIR="$2"

if [ ! -d "$LOCAL_DIR" ]; then
    echo "Error: Local directory not found: $LOCAL_DIR" >&2
    exit 1
fi

if [ ! -d "$UPSTREAM_DIR" ]; then
    echo "Error: Upstream directory not found: $UPSTREAM_DIR" >&2
    exit 1
fi

# Find files with async-profiler copyright using grep
grep -rl "Copyright.*async-profiler authors" "$LOCAL_DIR" --include="*.cpp" --include="*.h" 2>/dev/null | while read -r local_file; do
    basename_file=$(basename "$local_file")

    # Check if corresponding file exists in upstream
    upstream_file="$UPSTREAM_DIR/$basename_file"
    if [ ! -f "$upstream_file" ]; then
        continue
    fi

    # Output relative path from upstream repo root
    echo "src/$basename_file"
done | sort -u
