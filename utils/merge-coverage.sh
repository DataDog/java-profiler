#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc
#
# Merge coverage exported by `run-containers-tests.sh --coverage-out=DIR` from several
# platform cells into one C++ (gcovr) and one Java (JaCoCo) report.
#
# Usage: ./utils/merge-coverage.sh --source-root=DIR --out=DIR CELL_DIR...
#   --source-root=DIR  checkout of the commit every cell was built from (report sources)
#   --out=DIR          output directory (cpp/, java/, summary.md)
#   CELL_DIR           a --coverage-out directory; needs cell.properties
#
# Requires gcovr 8.3+ and java. The JaCoCo CLI is taken from $JACOCO_CLI, else
# downloaded from Maven Central into DIR/tools.

set -euo pipefail

JACOCO_VERSION="0.8.14"
SOURCE_ROOT=""
OUT=""
CELLS=()

usage() {
    awk 'NR >= 4 && NR <= 13 { sub(/^# ?/, ""); print }' "$0"
    exit "${1:-0}"
}

die() {
    echo "Error: $*" >&2
    exit 1
}

prop() {
    sed -n "s/^$2=//p" "$1/cell.properties"
}

for arg in "$@"; do
    case "$arg" in
        --source-root=*) SOURCE_ROOT="${arg#*=}" ;;
        --out=*) OUT="${arg#*=}" ;;
        --help|-h) usage 0 ;;
        -*) echo "Unknown option: $arg" >&2; usage 1 ;;
        *) CELLS+=("$arg") ;;
    esac
done

[[ -n "$SOURCE_ROOT" ]] || die "--source-root is required"
[[ -n "$OUT" ]] || die "--out is required"
(( ${#CELLS[@]} > 0 )) || die "no cell directories given"
CPP_SRC="$SOURCE_ROOT/ddprof-lib/src/main/cpp"
JAVA_SRC="$SOURCE_ROOT/ddprof-lib/src/main/java"
[[ -d "$CPP_SRC" && -d "$JAVA_SRC" ]] || die "$SOURCE_ROOT is not a java-profiler checkout"

# Every cell must come from one commit: gcovr matches lines by number, and JaCoCo
# ignores execution data recorded against different class bytes.
COMMIT=""
for cell in "${CELLS[@]}"; do
    [[ -f "$cell/cell.properties" ]] || die "$cell has no cell.properties"
    cell_commit=$(prop "$cell" commit)
    if [[ -z "$COMMIT" ]]; then
        COMMIT=$cell_commit
    elif [[ "$cell_commit" != "$COMMIT" ]]; then
        die "$cell was built from $cell_commit, other cells from $COMMIT"
    fi
done
source_commit=$(git -C "$SOURCE_ROOT" rev-parse HEAD 2>/dev/null || true)
if [[ "$source_commit" != "$COMMIT" ]]; then
    die "--source-root is at ${source_commit:-<not a git checkout>}, cells were built from $COMMIT"
fi

mkdir -p "$OUT/cpp" "$OUT/java"
OUT="$(cd "$OUT" && pwd)"

# ---- C++ ----
tracefiles=()
for cell in "${CELLS[@]}"; do
    if [[ -f "$cell/reports/cpp/coverage.json" ]]; then
        tracefiles+=(--add-tracefile "$cell/reports/cpp/coverage.json")
    else
        echo "Warning: $cell has no C++ tracefile; it is left out of the C++ report" >&2
    fi
done
CPP_SUMMARY="(no C++ tracefiles)"
if (( ${#tracefiles[@]} > 0 )); then
    # Compilers differ between cells (glibc vs musl toolchains), so a function can be
    # reported at different lines; keep those entries apart instead of failing.
    gcovr --root "$CPP_SRC" "${tracefiles[@]}" \
        --merge-mode-functions=separate \
        --html --html-details -o "$OUT/cpp/index.html" \
        --json "$OUT/cpp/coverage.json" \
        --print-summary | tee "$OUT/cpp/summary.txt"
    CPP_SUMMARY=$(cat "$OUT/cpp/summary.txt")
fi

# ---- Java ----
execs=()
CLASSES=""
for cell in "${CELLS[@]}"; do
    if [[ -d "$cell/jacoco" ]]; then
        while IFS= read -r f; do
            execs+=("$f")
        done < <(find "$cell/jacoco" -name '*.exec' -type f | sort)
    fi
    if [[ -d "$cell/classes" ]]; then
        if [[ -z "$CLASSES" ]]; then
            CLASSES="$cell/classes"
        elif ! diff -rq "$CLASSES" "$cell/classes" >/dev/null; then
            echo "Warning: classes in $cell differ from $CLASSES; JaCoCo drops its data for the differing classes" >&2
        fi
    fi
done
JAVA_SUMMARY="(no JaCoCo execution data)"
if (( ${#execs[@]} > 0 )) && [[ -n "$CLASSES" ]]; then
    cli="${JACOCO_CLI:-}"
    if [[ -z "$cli" ]]; then
        cli="$OUT/tools/org.jacoco.cli-$JACOCO_VERSION-nodeps.jar"
        if [[ ! -f "$cli" ]]; then
            mkdir -p "$OUT/tools"
            url="https://repo1.maven.org/maven2/org/jacoco/org.jacoco.cli/$JACOCO_VERSION/org.jacoco.cli-$JACOCO_VERSION-nodeps.jar"
            curl -fsSL -o "$cli.tmp" "$url"
            expected=$(curl -fsSL "$url.sha1" | cut -c1-40)
            actual=$( (shasum -a 1 "$cli.tmp" 2>/dev/null || sha1sum "$cli.tmp") | cut -c1-40)
            [[ "$expected" == "$actual" ]] || die "SHA-1 mismatch for $url"
            mv "$cli.tmp" "$cli"
        fi
    fi
    java -jar "$cli" merge "${execs[@]}" --destfile "$OUT/java/merged.exec"
    java -jar "$cli" report "$OUT/java/merged.exec" \
        --classfiles "$CLASSES" --sourcefiles "$JAVA_SRC" \
        --html "$OUT/java/html" --xml "$OUT/java/jacoco.xml"
    JAVA_SUMMARY=$(python3 -I - "$OUT/java/jacoco.xml" <<'EOF'
import sys
import xml.etree.ElementTree as ET

root = ET.parse(sys.argv[1]).getroot()
for c in root.findall("counter"):
    covered, missed = int(c.get("covered")), int(c.get("missed"))
    total = covered + missed
    pct = 100.0 * covered / total if total else 0.0
    print(f"{c.get('type').lower()}: {pct:.1f}% ({covered} out of {total})")
EOF
)
fi

# ---- Summary ----
{
    echo "# Merged coverage"
    echo
    echo "- Commit: \`$COMMIT\`"
    echo "- C++ report: \`cpp/index.html\`"
    echo "- Java report: \`java/html/index.html\`"
    echo
    echo "| libc | arch | jdk | gradle exit |"
    echo "|---|---|---|---|"
    for cell in "${CELLS[@]}"; do
        echo "| $(prop "$cell" libc) | $(prop "$cell" arch) | $(prop "$cell" jdk) | $(prop "$cell" gradle_exit) |"
    done
    echo
    echo "## C++ (debug build, all cells)"
    echo
    echo '```text'
    echo "$CPP_SUMMARY"
    echo '```'
    echo
    echo "## Java (all cells)"
    echo
    echo '```text'
    echo "$JAVA_SUMMARY"
    echo '```'
} > "$OUT/summary.md"

echo ">>> Merged coverage written to $OUT (summary.md, cpp/index.html, java/html/index.html)"
