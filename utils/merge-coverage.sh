#!/usr/bin/env bash
# Copyright 2026, Datadog, Inc
#
# Merge coverage exported by `run-containers-tests.sh --coverage-out=DIR` from several
# platform cells into one C++ (gcovr) and one Java (JaCoCo) report.
#
# Usage: ./utils/merge-coverage.sh --source-root=DIR --out=DIR CELL_DIR...
#   --source-root=DIR  checkout of the commit every cell was built from (report sources)
#   --out=DIR          output directory (cpp/, java/, summary.md); replaced on each run
#   CELL_DIR           a --coverage-out directory; needs cell.properties
#
# Requires java, python3 and a gcovr at least as new as the containers' (older ones
# reject their tracefiles). The JaCoCo CLI is $JACOCO_CLI, else downloaded with curl.

set -euo pipefail

# Must match jacoco.toolVersion in ddprof-test/build.gradle.kts.
JACOCO_VERSION="0.8.14"
JACOCO_CLI_SHA256="811c7f8c6b358c5d68a8973cfa867f6892be7a671b697a4b13c4b447e6daf75c"
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
    [[ -n "$cell_commit" ]] || die "$cell has no commit in cell.properties"
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

# HEAD only names the commit; edited sources would be reported against line numbers and
# class contents the cells never built.
if [[ -n "$(git -C "$SOURCE_ROOT" status --porcelain --untracked-files=no -- ddprof-lib/src/main 2>/dev/null)" ]]; then
    die "--source-root has uncommitted changes under ddprof-lib/src/main; the cells were built from $COMMIT"
fi

mkdir -p "$OUT"
OUT="$(cd "$OUT" && pwd)"
# --out is replaced, so it must be empty or carry the marker an earlier merge wrote.
MARKER=".merge-coverage-output"
if [[ -n "$(ls -A "$OUT")" && ! -f "$OUT/$MARKER" ]]; then
    die "--out $OUT is neither empty nor an earlier merge output"
fi
touch "$OUT/$MARKER"
# Keep tools/ (the downloaded CLI); a report left from an earlier merge would be linked
# from this run's summary.
rm -rf "$OUT/cpp" "$OUT/java" "$OUT/summary.md"
mkdir -p "$OUT/cpp" "$OUT/java"

# Per-cell inclusion, indexed like CELLS (bash 3.2 has no associative arrays).
CELL_CPP=()
CELL_JAVA=()

# ---- C++ ----
tracefiles=()
for i in "${!CELLS[@]}"; do
    cell=${CELLS[$i]}
    if [[ -f "$cell/reports/cpp/coverage.json" ]]; then
        tracefiles+=(--add-tracefile "$cell/reports/cpp/coverage.json")
        CELL_CPP[$i]=yes
    else
        echo "Warning: $cell has no C++ tracefile; it is left out of the C++ report" >&2
        CELL_CPP[$i]="no (no tracefile)"
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
# Digest of a class tree (names and bytes), to find the classes most cells agree on.
tree_digest() {
    (cd "$1" && find . -type f -print0 | LC_ALL=C sort -z | xargs -0 cat \
        && find . -type f | LC_ALL=C sort) | { shasum -a 256 2>/dev/null || sha256sum; } | cut -c1-64
}
execs=()
CLASSES=""
# Reference classes: the tree most cells with JaCoCo data share, so one odd cell cannot
# mark all the others partial. Ties go to the first cell.
CELL_DIGEST=()
for i in "${!CELLS[@]}"; do
    cell=${CELLS[$i]}
    CELL_DIGEST[$i]=""
    [[ -d "$cell/classes" && -d "$cell/jacoco" ]] || continue
    [[ -n "$(find "$cell/jacoco" -name '*.exec' -type f | head -1)" ]] || continue
    CELL_DIGEST[$i]=$(tree_digest "$cell/classes")
done
best=0
for i in "${!CELLS[@]}"; do
    [[ -n "${CELL_DIGEST[$i]}" ]] || continue
    n=0
    for j in "${!CELLS[@]}"; do
        [[ "${CELL_DIGEST[$j]}" != "${CELL_DIGEST[$i]}" ]] || n=$((n + 1))
    done
    if (( n > best )); then
        best=$n
        CLASSES="${CELLS[$i]}/classes"
    fi
done
for i in "${!CELLS[@]}"; do
    cell=${CELLS[$i]}
    cell_execs=0
    if [[ -d "$cell/jacoco" ]]; then
        while IFS= read -r f; do
            execs+=("$f")
            cell_execs=$((cell_execs + 1))
        done < <(find "$cell/jacoco" -name '*.exec' -type f | sort)
    fi
    if (( cell_execs == 0 )); then
        CELL_JAVA[$i]="no (no JaCoCo data)"
    elif [[ ! -d "$cell/classes" ]]; then
        # Nothing to compare: JaCoCo may drop this cell's data for classes that differ.
        CELL_JAVA[$i]="unverified (no classes)"
    elif diff -rq "$CLASSES" "$cell/classes" >/dev/null; then
        CELL_JAVA[$i]=yes
    else
        echo "Warning: classes in $cell differ from $CLASSES; JaCoCo drops its data for the differing classes" >&2
        CELL_JAVA[$i]="partial (classes differ)"
    fi
done
JAVA_SUMMARY="(no JaCoCo execution data)"
if (( ${#execs[@]} > 0 )) && [[ -z "$CLASSES" ]]; then
    JAVA_SUMMARY="(no cell exported classes)"
    for i in "${!CELLS[@]}"; do
        case "${CELL_JAVA[$i]}" in
            yes|unverified*) CELL_JAVA[$i]="no (no classes in any cell)" ;;
        esac
    done
fi
if (( ${#execs[@]} > 0 )) && [[ -n "$CLASSES" ]]; then
    cli="${JACOCO_CLI:-}"
    if [[ -n "$cli" ]]; then
        echo "Warning: using \$JACOCO_CLI=$cli unverified; the pinned $JACOCO_VERSION jar is checked only when downloaded" >&2
    else
        cli="$OUT/tools/org.jacoco.cli-$JACOCO_VERSION-nodeps.jar"
        if [[ ! -f "$cli" ]]; then
            mkdir -p "$OUT/tools"
            url="https://repo1.maven.org/maven2/org/jacoco/org.jacoco.cli/$JACOCO_VERSION/org.jacoco.cli-$JACOCO_VERSION-nodeps.jar"
            curl -fsSL --connect-timeout 20 --max-time 300 --retry 3 -o "$cli.tmp" "$url"
            actual=$( (shasum -a 256 "$cli.tmp" 2>/dev/null || sha256sum "$cli.tmp") | cut -c1-64)
            if [[ "$actual" != "$JACOCO_CLI_SHA256" ]]; then
                rm -f "$cli.tmp"
                die "SHA-256 mismatch for $url"
            fi
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
FILTERED=false
for cell in "${CELLS[@]}"; do
    [[ -z "$(prop "$cell" tests)" ]] || FILTERED=true
done
{
    echo "# Merged coverage"
    echo
    echo "- Commit: \`$COMMIT\`"
    if [[ -f "$OUT/cpp/index.html" ]]; then
        echo "- C++ report: \`cpp/index.html\`"
    fi
    if [[ -f "$OUT/java/html/index.html" ]]; then
        echo "- Java report: \`java/html/index.html\`"
    fi
    if $FILTERED; then
        echo "- Filtered run: some cells ran only the tests matching their \`tests\` pattern"
    fi
    echo
    echo "| libc | arch | jdk | tests | gradle exit | in C++ report | in Java report |"
    echo "|---|---|---|---|---|---|---|"
    for i in "${!CELLS[@]}"; do
        cell=${CELLS[$i]}
        echo "| $(prop "$cell" libc) | $(prop "$cell" arch) | $(prop "$cell" jdk) | $(t=$(prop "$cell" tests); echo "${t//|/\\|}") | $(prop "$cell" gradle_exit) | ${CELL_CPP[$i]} | ${CELL_JAVA[$i]} |"
    done
    echo
    echo "## C++ (debug build, cells marked in the C++ column)"
    echo
    echo '```text'
    echo "$CPP_SUMMARY"
    echo '```'
    echo
    echo "## Java (cells marked in the Java column)"
    echo
    echo '```text'
    echo "$JAVA_SUMMARY"
    echo '```'
} > "$OUT/summary.md"

echo ">>> Merged coverage written to $OUT (summary.md, cpp/index.html, java/html/index.html)"
