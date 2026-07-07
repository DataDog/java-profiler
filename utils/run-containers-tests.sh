#!/bin/bash
# Copyright 2026, Datadog, Inc
#
# Run tests in containers with various OS/libc/JDK combinations (similar to CI)
# Defaults to Podman; use --container=docker to use Docker.
# Uses two-level container image caching:
#   1. Base image with OS + build tools (java-profiler-base:<libc>-<arch>)
#   2. JDK-specific image on top (java-profiler-test:<libc>-jdk<version>-<arch>)
#
# Usage: ./utils/run-containers-tests.sh [options]
#   --libc=glibc|musl|all[,..]    (default: glibc)
#   --jdk=8|11|17|21|25|8-j9|11-j9|17-j9|21-j9|17-graal|21-graal|25-graal|regular|j9|graal|all[,..]
#                                   (default: 21)
#   --arch=x64|aarch64|all[,..]   (default: auto-detect)
#   --config=debug|release|asan|tsan|all[,..]   (default: debug)
#   --container=podman|docker  (default: podman)
#   --tests="TestPattern"    (optional, specific test to run)
#   --gtest                  (enable C++ gtests, disabled by default)
#   --gtest-task=Task        (run one C++ gtest task; accepts elfparser_ut or :ddprof-lib:gtestAsan_elfparser_ut)
#   --shell                  (drop to shell instead of running tests; enables SYS_PTRACE for gdb)
#   --mount                  (mount local repo instead of cloning - faster but may have stale artifacts)
#   --rebuild                (force rebuild of container images)
#   --rebuild-base           (force rebuild of base image only)
#   --matrix                 (preview a full matrix; unset dimensions expand to all)
#   --run                    (execute an inferred matrix without prompting)
#   --fail-fast              (stop matrix execution on first failure)
#   --help                   (show this help)

set -e

# Defaults
ORIGINAL_ARGS=("$@")
CONTAINER_RUNTIME="${CONTAINER_RUNTIME:-podman}"
LIBC="glibc"
JDK_VERSION="21"
ARCH=""
CONFIG="debug"
TESTS=""
GTEST_TASK=""
SHELL_MODE=false
MOUNT_MODE=false
GTEST_ENABLED=false
REBUILD=false
REBUILD_BASE=false
MATRIX_MODE=false
RUN_MATRIX=false
FAIL_FAST=false
LIBC_SET=false
JDK_SET=false
ARCH_SET=false
CONFIG_SET=false
PASS_THROUGH_ARGS=()
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BASE_IMAGE_PREFIX="java-profiler-base"
IMAGE_PREFIX="java-profiler-test"

selinux_enforcing() {
    if [[ -r /sys/fs/selinux/enforce ]]; then
        [[ "$(cat /sys/fs/selinux/enforce)" == "1" ]]
    elif command -v getenforce >/dev/null 2>&1; then
        [[ "$(getenforce)" == "Enforcing" ]]
    else
        false
    fi
}

# Auto-detect architecture
detect_arch() {
    local machine
    machine=$(uname -m)
    case "$machine" in
        x86_64|amd64)
            echo "x64"
            ;;
        aarch64|arm64)
            echo "aarch64"
            ;;
        *)
            echo "x64"  # default fallback
            ;;
    esac
}

# JDK Download URLs (Bellsoft Liberica for musl)
get_musl_jdk_url() {
    local version=$1
    local arch=$2

    case "$version-$arch" in
        8-x64)      echo "https://download.bell-sw.com/java/8u462+11/bellsoft-jdk8u462+11-linux-x64-musl-lite.tar.gz" ;;
        8-aarch64)  echo "https://download.bell-sw.com/java/8u462+11/bellsoft-jdk8u462+11-linux-aarch64-musl-lite.tar.gz" ;;
        11-x64)     echo "https://download.bell-sw.com/java/11.0.28+12/bellsoft-jdk11.0.28+12-linux-x64-musl-lite.tar.gz" ;;
        11-aarch64) echo "https://download.bell-sw.com/java/11.0.28+12/bellsoft-jdk11.0.28+12-linux-aarch64-musl-lite.tar.gz" ;;
        17-x64)     echo "https://download.bell-sw.com/java/17.0.16+12/bellsoft-jdk17.0.16+12-linux-x64-musl-lite.tar.gz" ;;
        17-aarch64) echo "https://download.bell-sw.com/java/17.0.16+12/bellsoft-jdk17.0.16+12-linux-aarch64-musl-lite.tar.gz" ;;
        21-x64)     echo "https://download.bell-sw.com/java/21.0.8+12/bellsoft-jdk21.0.8+12-linux-x64-musl-lite.tar.gz" ;;
        21-aarch64) echo "https://download.bell-sw.com/java/21.0.8+12/bellsoft-jdk21.0.8+12-linux-aarch64-musl-lite.tar.gz" ;;
        25-x64)     echo "https://download.bell-sw.com/java/25.0.2+12/bellsoft-jdk25.0.2+12-linux-x64-musl-lite.tar.gz" ;;
        25-aarch64) echo "https://download.bell-sw.com/java/25.0.2+12/bellsoft-jdk25.0.2+12-linux-aarch64-musl-lite.tar.gz" ;;
        *)          echo "" ;;
    esac
}

# JDK Download URLs (Eclipse Temurin for glibc)
get_glibc_jdk_url() {
    local version=$1
    local arch=$2

    case "$version-$arch" in
        8-x64)      echo "https://github.com/adoptium/temurin8-binaries/releases/download/jdk8u462-b08/OpenJDK8U-jdk_x64_linux_hotspot_8u462b08.tar.gz" ;;
        8-aarch64)  echo "https://github.com/adoptium/temurin8-binaries/releases/download/jdk8u462-b08/OpenJDK8U-jdk_aarch64_linux_hotspot_8u462b08.tar.gz" ;;
        11-x64)     echo "https://github.com/adoptium/temurin11-binaries/releases/download/jdk-11.0.28%2B6/OpenJDK11U-jdk_x64_linux_hotspot_11.0.28_6.tar.gz" ;;
        11-aarch64) echo "https://github.com/adoptium/temurin11-binaries/releases/download/jdk-11.0.28%2B6/OpenJDK11U-jdk_aarch64_linux_hotspot_11.0.28_6.tar.gz" ;;
        17-x64)     echo "https://github.com/adoptium/temurin17-binaries/releases/download/jdk-17.0.16%2B8/OpenJDK17U-jdk_x64_linux_hotspot_17.0.16_8.tar.gz" ;;
        17-aarch64) echo "https://github.com/adoptium/temurin17-binaries/releases/download/jdk-17.0.16%2B8/OpenJDK17U-jdk_aarch64_linux_hotspot_17.0.16_8.tar.gz" ;;
        21-x64)     echo "https://github.com/adoptium/temurin21-binaries/releases/download/jdk-21.0.8%2B9/OpenJDK21U-jdk_x64_linux_hotspot_21.0.8_9.tar.gz" ;;
        21-aarch64) echo "https://github.com/adoptium/temurin21-binaries/releases/download/jdk-21.0.8%2B9/OpenJDK21U-jdk_aarch64_linux_hotspot_21.0.8_9.tar.gz" ;;
        25-x64)     echo "https://github.com/adoptium/temurin25-binaries/releases/download/jdk-25.0.2%2B10/OpenJDK25U-jdk_x64_linux_hotspot_25.0.2_10.tar.gz" ;;
        25-aarch64) echo "https://github.com/adoptium/temurin25-binaries/releases/download/jdk-25.0.2%2B10/OpenJDK25U-jdk_aarch64_linux_hotspot_25.0.2_10.tar.gz" ;;
        *)          echo "" ;;
    esac
}

# JDK Download URLs (Oracle GraalVM)
# Versions match the SDKMAN-installed builds used in CI (java_setup.sh +
# cache_java.yml: JAVA_<v>_GRAAL_VERSION).  Using Oracle's stable archive
# URLs (not "latest") so the docker images match the CI configuration.
get_graal_jdk_url() {
    local version=$1
    local arch=$2
    # Oracle GraalVM archive arch labels: x64 / aarch64 (same as our $arch)
    case "$version-$arch" in
        17-x64)     echo "https://download.oracle.com/graalvm/17/archive/graalvm-jdk-17.0.12_linux-x64_bin.tar.gz" ;;
        17-aarch64) echo "https://download.oracle.com/graalvm/17/archive/graalvm-jdk-17.0.12_linux-aarch64_bin.tar.gz" ;;
        21-x64)     echo "https://download.oracle.com/graalvm/21/archive/graalvm-jdk-21.0.4_linux-x64_bin.tar.gz" ;;
        21-aarch64) echo "https://download.oracle.com/graalvm/21/archive/graalvm-jdk-21.0.4_linux-aarch64_bin.tar.gz" ;;
        25-x64)     echo "https://download.oracle.com/graalvm/25/archive/graalvm-jdk-25_linux-x64_bin.tar.gz" ;;
        25-aarch64) echo "https://download.oracle.com/graalvm/25/archive/graalvm-jdk-25_linux-aarch64_bin.tar.gz" ;;
        *)          echo "" ;;
    esac
}

# JDK Download URLs (IBM Semeru OpenJ9)
get_j9_jdk_url() {
    local version=$1
    local arch=$2

    case "$version-$arch" in
        8-x64)      echo "https://github.com/ibmruntimes/semeru8-binaries/releases/download/jdk8u482-b08_openj9-0.57.0/ibm-semeru-open-jdk_x64_linux_8u482b08_openj9-0.57.0.tar.gz" ;;
        8-aarch64)  echo "https://github.com/ibmruntimes/semeru8-binaries/releases/download/jdk8u482-b08_openj9-0.57.0/ibm-semeru-open-jdk_aarch64_linux_8u482b08_openj9-0.57.0.tar.gz" ;;
        11-x64)     echo "https://github.com/ibmruntimes/semeru11-binaries/releases/download/jdk-11.0.30%2B7_openj9-0.57.0/ibm-semeru-open-jdk_x64_linux_11.0.30_7_openj9-0.57.0.tar.gz" ;;
        11-aarch64) echo "https://github.com/ibmruntimes/semeru11-binaries/releases/download/jdk-11.0.30%2B7_openj9-0.57.0/ibm-semeru-open-jdk_aarch64_linux_11.0.30_7_openj9-0.57.0.tar.gz" ;;
        17-x64)     echo "https://github.com/ibmruntimes/semeru17-binaries/releases/download/jdk-17.0.18%2B8_openj9-0.57.0/ibm-semeru-open-jdk_x64_linux_17.0.18_8_openj9-0.57.0.tar.gz" ;;
        17-aarch64) echo "https://github.com/ibmruntimes/semeru17-binaries/releases/download/jdk-17.0.18%2B8_openj9-0.57.0/ibm-semeru-open-jdk_aarch64_linux_17.0.18_8_openj9-0.57.0.tar.gz" ;;
        21-x64)     echo "https://github.com/ibmruntimes/semeru21-binaries/releases/download/jdk-21.0.10%2B7_openj9-0.57.0/ibm-semeru-open-jdk_x64_linux_21.0.9_10_openj9-0.56.0.tar.gz" ;;
        21-aarch64) echo "https://github.com/ibmruntimes/semeru21-binaries/releases/download/jdk-21.0.10%2B7_openj9-0.57.0/ibm-semeru-open-jdk_aarch64_linux_21.0.9_10_openj9-0.56.0.tar.gz" ;;
        *)          echo "" ;;
    esac
}

join_by() {
    local delimiter=$1
    shift
    local first=true
    local item
    for item in "$@"; do
        if $first; then
            printf "%s" "$item"
            first=false
        else
            printf "%s%s" "$delimiter" "$item"
        fi
    done
}

json_escape() {
    local value=$1
    value=${value//\\/\\\\}
    value=${value//\"/\\\"}
    value=${value//$'\n'/\\n}
    value=${value//$'\r'/\\r}
    value=${value//$'\t'/\\t}
    printf "%s" "$value"
}

original_command() {
    if [[ ${#ORIGINAL_ARGS[@]} -eq 0 ]]; then
        echo "./utils/run-containers-tests.sh"
    else
        echo "./utils/run-containers-tests.sh $(join_by " " "${ORIGINAL_ARGS[@]}")"
    fi
}

contains_value() {
    local needle=$1
    shift
    local value
    for value in "$@"; do
        if [[ "$value" == "$needle" ]]; then
            return 0
        fi
    done
    return 1
}

append_unique_line() {
    local array_name=$1
    local value=$2

    eval "contains_value \"\$value\" \"\${${array_name}[@]}\"" && return
    eval "$array_name+=(\"\$value\")"
}

read_lines_into_array() {
    local array_name=$1
    local line
    eval "$array_name=()"
    while IFS= read -r line; do
        eval "$array_name+=(\"\$line\")"
    done
}

read_string_into_array() {
    local array_name=$1
    local values=$2
    local line
    eval "$array_name=()"
    while IFS= read -r line; do
        eval "$array_name+=(\"\$line\")"
    done <<< "$values"
}

expand_dimension() {
    local value=$1
    local name=$2
    shift 2
    local all_values=("$@")
    local expanded=()
    local token

    IFS=',' read -ra tokens <<< "$value"
    for token in "${tokens[@]}"; do
        if [[ -z "$token" ]]; then
            echo "Error: --$name contains an empty value" >&2
            exit 1
        elif [[ "$token" == "all" ]]; then
            local all_value
            for all_value in "${all_values[@]}"; do
                append_unique_line expanded "$all_value"
            done
        elif contains_value "$token" "${all_values[@]}"; then
            append_unique_line expanded "$token"
        else
            echo "Error: --$name must be one or more of: $(join_by "|" "${all_values[@]}")|all" >&2
            exit 1
        fi
    done

    printf "%s\n" "${expanded[@]}"
}

expand_jdk_dimension() {
    local value=$1
    local regular_jdks=(8 11 17 21 25)
    local j9_jdks=(8-j9 11-j9 17-j9 21-j9)
    local graal_jdks=(17-graal 21-graal 25-graal)
    local all_jdks=("${regular_jdks[@]}" "${j9_jdks[@]}" "${graal_jdks[@]}")
    local expanded=()
    local token

    IFS=',' read -ra tokens <<< "$value"
    for token in "${tokens[@]}"; do
        case "$token" in
            "")
                echo "Error: --jdk contains an empty value" >&2
                exit 1
                ;;
            all)
                local all_jdk
                for all_jdk in "${all_jdks[@]}"; do
                    append_unique_line expanded "$all_jdk"
                done
                ;;
            regular)
                local regular_jdk
                for regular_jdk in "${regular_jdks[@]}"; do
                    append_unique_line expanded "$regular_jdk"
                done
                ;;
            j9)
                local j9_jdk
                for j9_jdk in "${j9_jdks[@]}"; do
                    append_unique_line expanded "$j9_jdk"
                done
                ;;
            graal)
                local graal_jdk
                for graal_jdk in "${graal_jdks[@]}"; do
                    append_unique_line expanded "$graal_jdk"
                done
                ;;
            *)
                if contains_value "$token" "${all_jdks[@]}"; then
                    append_unique_line expanded "$token"
                else
                    echo "Error: --jdk must be one or more of: 8|11|17|21|25|8-j9|11-j9|17-j9|21-j9|17-graal|21-graal|25-graal|regular|j9|graal|all" >&2
                    exit 1
                fi
                ;;
        esac
    done

    printf "%s\n" "${expanded[@]}"
}

skip_reason() {
    local libc=$1
    local jdk=$2
    local config=$3

    if [[ "$libc" == "musl" && "$jdk" == *-j9 ]]; then
        echo "J9/OpenJ9 is not available for musl libc"
    elif [[ "$libc" == "musl" && "$jdk" == *-graal ]]; then
        echo "GraalVM is not available for musl libc"
    elif [[ "$libc" == "musl" && ( "$config" == "asan" || "$config" == "tsan" ) ]]; then
        echo "sanitizer configs are filtered out for musl in CI"
    fi
}

matrix_command() {
    local libc=$1
    local arch=$2
    local jdk=$3
    local config=$4
    local cmd=("./utils/run-containers-tests.sh" "--libc=$libc" "--arch=$arch" "--jdk=$jdk" "--config=$config")

    if [[ ${#PASS_THROUGH_ARGS[@]} -gt 0 ]]; then
        cmd+=("${PASS_THROUGH_ARGS[@]}")
    fi

    printf "%q " "${cmd[@]}"
}

cell_status_symbol() {
    local status=$1
    local style=${2:-text}

    case "$status" in
        pending)
            printf "TODO"
            ;;
        passed)
            if [[ "$style" == "emoji" ]]; then
                printf "✅"
            else
                printf "PASS"
            fi
            ;;
        failed)
            if [[ "$style" == "emoji" ]]; then
                printf "❌"
            else
                printf "FAIL"
            fi
            ;;
        skipped)
            printf "-"
            ;;
        cancelled)
            if [[ "$style" == "emoji" ]]; then
                printf "🚫"
            else
                printf "CANCEL"
            fi
            ;;
        *)
            printf "%s" "$status"
            ;;
    esac
}

matrix_column_name() {
    local libc=$1
    local arch=$2
    local config=$3
    local arch_label=$arch

    if [[ "$arch_label" == "x64" ]]; then
        arch_label="amd64"
    fi

    printf "%s-%s/%s" "$libc" "$arch_label" "$config"
}

repeat_char() {
    local char=$1
    local count=$2
    local i

    for ((i = 0; i < count; i++)); do
        printf "%s" "$char"
    done
}

display_width() {
    local value=$1

    case "$value" in
        "✅"|"❌"|"🚫")
            printf "2"
            ;;
        *)
            printf "%d" "${#value}"
            ;;
    esac
}

print_padded() {
    local value=$1
    local width=$2
    local visible_width
    local padding

    visible_width=$(display_width "$value")
    padding=$((width - visible_width))
    printf "%s" "$value"
    if (( padding > 0 )); then
        repeat_char " " "$padding"
    fi
}

print_table_separator() {
    local jdk_width=$1
    local status_width=$2
    local columns=$3
    local i

    printf "+"
    repeat_char "-" "$((jdk_width + 2))"
    printf "+"
    for ((i = 0; i < columns; i++)); do
        repeat_char "-" "$((status_width + 2))"
        printf "+"
    done
    printf "\n"
}

print_matrix_status_table() {
    local style=${1:-text}
    local i row col cell_value
    local columns=()
    local rows=()
    local jdk_width=3
    local status_width=4

    for ((i = 0; i < ${#MATRIX_CELL_LIBCS[@]}; i++)); do
        append_unique_line columns "$(matrix_column_name "${MATRIX_CELL_LIBCS[$i]}" "${MATRIX_CELL_ARCHES[$i]}" "${MATRIX_CELL_CONFIGS[$i]}")"
        append_unique_line rows "${MATRIX_CELL_JDKS[$i]}"
    done

    for row in "${rows[@]}"; do
        if (( ${#row} > jdk_width )); then
            jdk_width=${#row}
        fi
    done
    for col in "${columns[@]}"; do
        if (( ${#col} > status_width )); then
            status_width=${#col}
        fi
    done

    echo "Status overview"
    echo
    print_table_separator "$jdk_width" "$status_width" "${#columns[@]}"
    printf "| "
    print_padded "JDK" "$jdk_width"
    printf " |"
    for col in "${columns[@]}"; do
        printf " "
        print_padded "$col" "$status_width"
        printf " |"
    done
    printf "\n"
    print_table_separator "$jdk_width" "$status_width" "${#columns[@]}"

    for row in "${rows[@]}"; do
        printf "| "
        print_padded "$row" "$jdk_width"
        printf " |"
        for ((j = 0; j < ${#columns[@]}; j++)); do
            col="${columns[$j]}"
            cell_value=""
            for ((i = 0; i < ${#MATRIX_CELL_LIBCS[@]}; i++)); do
                if [[ "${MATRIX_CELL_JDKS[$i]}" == "$row" ]] && [[ "$(matrix_column_name "${MATRIX_CELL_LIBCS[$i]}" "${MATRIX_CELL_ARCHES[$i]}" "${MATRIX_CELL_CONFIGS[$i]}")" == "$col" ]]; then
                    cell_value=$(cell_status_symbol "${MATRIX_CELL_STATUSES[$i]}" "$style")
                    break
                fi
            done
            printf " "
            print_padded "${cell_value:--}" "$status_width"
            printf " |"
        done
        printf "\n"
    done
    print_table_separator "$jdk_width" "$status_width" "${#columns[@]}"
}

print_matrix_legend() {
    echo "Legend: ✅ passed | ❌ failed | - skipped | 🚫 cancelled"
}

print_failed_cells() {
    local i has_failures=false

    for ((i = 0; i < ${#MATRIX_CELL_LIBCS[@]}; i++)); do
        if [[ "${MATRIX_CELL_STATUSES[$i]}" == "failed" ]]; then
            if ! $has_failures; then
                echo
                echo "Failed cells:"
                has_failures=true
            fi
            echo "- jdk=${MATRIX_CELL_JDKS[$i]}, libc=${MATRIX_CELL_LIBCS[$i]}, arch=${MATRIX_CELL_ARCHES[$i]}, config=${MATRIX_CELL_CONFIGS[$i]}, exit_code=${MATRIX_CELL_EXIT_CODES[$i]}"
        fi
    done
}

prepare_matrix_cells() {
    local libc arch jdk config reason

    MATRIX_TOTAL=0
    MATRIX_RUNNABLE=0
    MATRIX_SKIPPED=0
    MATRIX_CELL_LIBCS=()
    MATRIX_CELL_ARCHES=()
    MATRIX_CELL_JDKS=()
    MATRIX_CELL_CONFIGS=()
    MATRIX_CELL_STATUSES=()
    MATRIX_CELL_EXIT_CODES=()
    MATRIX_CELL_REASONS=()

    for libc in "${MATRIX_LIBCS[@]}"; do
        for arch in "${MATRIX_ARCHES[@]}"; do
            for jdk in "${MATRIX_JDKS[@]}"; do
                for config in "${MATRIX_CONFIGS[@]}"; do
                    ((MATRIX_TOTAL += 1))
                    reason=$(skip_reason "$libc" "$jdk" "$config")
                    if [[ -n "$reason" ]]; then
                        ((MATRIX_SKIPPED += 1))
                        MATRIX_CELL_STATUSES+=("skipped")
                        MATRIX_CELL_EXIT_CODES+=("null")
                        MATRIX_CELL_REASONS+=("$reason")
                    else
                        ((MATRIX_RUNNABLE += 1))
                        MATRIX_CELL_STATUSES+=("pending")
                        MATRIX_CELL_EXIT_CODES+=("null")
                        MATRIX_CELL_REASONS+=("")
                    fi
                    MATRIX_CELL_LIBCS+=("$libc")
                    MATRIX_CELL_ARCHES+=("$arch")
                    MATRIX_CELL_JDKS+=("$jdk")
                    MATRIX_CELL_CONFIGS+=("$config")
                done
            done
        done
    done
}

print_matrix_preview() {
    echo "=== Container Test Matrix ==="
    echo "LIBC filter:   $LIBC"
    echo "Arch filter:   $ARCH"
    echo "JDK filter:    $JDK_VERSION"
    echo "Config filter: $CONFIG"
    echo "Runtime:       $CONTAINER_RUNTIME"
    echo "Mode:          $(if $RUN_MATRIX; then echo 'run'; else echo 'preview'; fi)"
    echo "============================="
    echo "Generated cells: $MATRIX_TOTAL"
    echo "Runnable cells:  $MATRIX_RUNNABLE"
    echo "Skipped cells:   $MATRIX_SKIPPED"
    echo
    print_matrix_status_table emoji
}

write_matrix_reports() {
    local start_time=$1
    local end_time=$2
    local passed=$3
    local failed=$4
    local skipped=$5
    local report_dir="$PROJECT_ROOT/build/reports/container-matrix"
    local markdown_report="$report_dir/summary.md"
    local json_report="$report_dir/summary.json"
    local i

    mkdir -p "$report_dir"

    {
        echo "# Container Matrix Summary"
        echo
        echo "- Command: \`$(original_command)\`"
        echo "- Started: $start_time"
        echo "- Finished: $end_time"
        echo "- Filters: libc=$LIBC, arch=$ARCH, jdk=$JDK_VERSION, config=$CONFIG"
        echo "- Totals: total=$MATRIX_TOTAL, passed=$passed, failed=$failed, skipped=$skipped"
        echo
        print_matrix_status_table emoji
        print_matrix_legend
        print_failed_cells
        echo
        echo "## Cells"
        for ((i = 0; i < ${#MATRIX_CELL_LIBCS[@]}; i++)); do
            echo "- libc=${MATRIX_CELL_LIBCS[$i]}, arch=${MATRIX_CELL_ARCHES[$i]}, jdk=${MATRIX_CELL_JDKS[$i]}, config=${MATRIX_CELL_CONFIGS[$i]}, status=${MATRIX_CELL_STATUSES[$i]}, exit_code=${MATRIX_CELL_EXIT_CODES[$i]}, reason=${MATRIX_CELL_REASONS[$i]:-}"
        done
    } > "$markdown_report"

    {
        echo "{"
        printf '  "command": "%s",\n' "$(json_escape "$(original_command)")"
        printf '  "started": "%s",\n' "$(json_escape "$start_time")"
        printf '  "finished": "%s",\n' "$(json_escape "$end_time")"
        printf '  "filters": {"libc": "%s", "arch": "%s", "jdk": "%s", "config": "%s"},\n' \
            "$(json_escape "$LIBC")" "$(json_escape "$ARCH")" "$(json_escape "$JDK_VERSION")" "$(json_escape "$CONFIG")"
        printf '  "totals": {"total": %d, "passed": %d, "failed": %d, "skipped": %d},\n' \
            "$MATRIX_TOTAL" "$passed" "$failed" "$skipped"
        echo '  "cells": ['
        for ((i = 0; i < ${#MATRIX_CELL_LIBCS[@]}; i++)); do
            printf '    {"libc": "%s", "arch": "%s", "jdk": "%s", "config": "%s", "status": "%s", "exit_code": %s, "reason": "%s"}' \
                "$(json_escape "${MATRIX_CELL_LIBCS[$i]}")" \
                "$(json_escape "${MATRIX_CELL_ARCHES[$i]}")" \
                "$(json_escape "${MATRIX_CELL_JDKS[$i]}")" \
                "$(json_escape "${MATRIX_CELL_CONFIGS[$i]}")" \
                "$(json_escape "${MATRIX_CELL_STATUSES[$i]}")" \
                "${MATRIX_CELL_EXIT_CODES[$i]}" \
                "$(json_escape "${MATRIX_CELL_REASONS[$i]:-}")"
            if (( i < ${#MATRIX_CELL_LIBCS[@]} - 1 )); then
                echo ","
            else
                echo
            fi
        done
        echo "  ]"
        echo "}"
    } > "$json_report"

    echo ">>> Matrix reports written:"
    echo ">>>   $markdown_report"
    echo ">>>   $json_report"
}

confirm_matrix_run() {
    local answer

    if $RUN_MATRIX; then
        return 0
    fi

    if [[ -t 0 ]]; then
        echo
        read -r -p "Run this matrix? [y/N] " answer
        case "$answer" in
            y|Y|yes|YES)
                return 0
                ;;
            *)
                echo "Preview only. Matrix was not run."
                return 1
                ;;
        esac
    fi

    echo
    echo "Preview only. Add --run to execute non-interactively."
    return 1
}

run_matrix() {
    local i j command exit_code
    local passed=0 failed=0 skipped=$MATRIX_SKIPPED overall_exit=0
    local start_time end_time

    if ! command -v "$CONTAINER_RUNTIME" >/dev/null 2>&1; then
        echo "Error: container runtime '$CONTAINER_RUNTIME' not found"
        echo "Use --container to select the runtime, e.g. $0 --container=docker ..."
        exit 1
    fi

    start_time=$(date -u +"%Y-%m-%dT%H:%M:%SZ")
    set +e
    for ((i = 0; i < ${#MATRIX_CELL_LIBCS[@]}; i++)); do
        if [[ "${MATRIX_CELL_STATUSES[$i]}" == "skipped" ]]; then
            continue
        fi

        echo
        echo ">>> Matrix cell $((i + 1))/${#MATRIX_CELL_LIBCS[@]}: libc=${MATRIX_CELL_LIBCS[$i]} arch=${MATRIX_CELL_ARCHES[$i]} jdk=${MATRIX_CELL_JDKS[$i]} config=${MATRIX_CELL_CONFIGS[$i]}"
        command=("$SCRIPT_DIR/run-containers-tests.sh"
            "--libc=${MATRIX_CELL_LIBCS[$i]}"
            "--arch=${MATRIX_CELL_ARCHES[$i]}"
            "--jdk=${MATRIX_CELL_JDKS[$i]}"
            "--config=${MATRIX_CELL_CONFIGS[$i]}")
        if [[ ${#PASS_THROUGH_ARGS[@]} -gt 0 ]]; then
            command+=("${PASS_THROUGH_ARGS[@]}")
        fi
        "${command[@]}"
        exit_code=$?

        MATRIX_CELL_EXIT_CODES[$i]=$exit_code
        if [[ $exit_code -eq 0 ]]; then
            MATRIX_CELL_STATUSES[$i]="passed"
            ((passed += 1))
        else
            MATRIX_CELL_STATUSES[$i]="failed"
            ((failed += 1))
            overall_exit=1
            if $FAIL_FAST; then
                echo ">>> Stopping after first failure because --fail-fast is set"
                for ((j = i + 1; j < ${#MATRIX_CELL_LIBCS[@]}; j++)); do
                    if [[ "${MATRIX_CELL_STATUSES[$j]}" == "pending" ]]; then
                        MATRIX_CELL_STATUSES[$j]="skipped"
                        MATRIX_CELL_REASONS[$j]="not run because --fail-fast stopped after an earlier failure"
                        ((skipped += 1))
                    fi
                done
                break
            fi
        fi
    done
    set -e

    end_time=$(date -u +"%Y-%m-%dT%H:%M:%SZ")
    write_matrix_reports "$start_time" "$end_time" "$passed" "$failed" "$skipped"

    echo
    echo "=== Matrix Result ==="
    echo "Passed:  $passed"
    echo "Failed:  $failed"
    echo "Skipped: $skipped"
    echo "====================="
    echo
    print_matrix_status_table emoji
    echo
    print_matrix_legend
    print_failed_cells

    exit "$overall_exit"
}

usage() {
    awk 'NR >= 4 && NR <= 27 { sub(/^# ?/, ""); print }' "$0"
    exit 0
}

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --libc=*)
            LIBC="${1#*=}"
            LIBC_SET=true
            shift
            ;;
        --jdk=*)
            JDK_VERSION="${1#*=}"
            JDK_SET=true
            shift
            ;;
        --arch=*)
            ARCH="${1#*=}"
            ARCH_SET=true
            shift
            ;;
        --config=*)
            CONFIG="${1#*=}"
            CONFIG_SET=true
            shift
            ;;
        --container=*)
            CONTAINER_RUNTIME="${1#*=}"
            PASS_THROUGH_ARGS+=("$1")
            shift
            ;;
        --tests=*)
            TESTS="${1#*=}"
            PASS_THROUGH_ARGS+=("$1")
            shift
            ;;
        --shell)
            SHELL_MODE=true
            shift
            ;;
        --mount)
            MOUNT_MODE=true
            PASS_THROUGH_ARGS+=("$1")
            shift
            ;;
        --gtest)
            GTEST_ENABLED=true
            PASS_THROUGH_ARGS+=("$1")
            shift
            ;;
        --gtest-task=*)
            GTEST_TASK="${1#*=}"
            GTEST_ENABLED=true
            PASS_THROUGH_ARGS+=("$1")
            shift
            ;;
        --rebuild)
            REBUILD=true
            PASS_THROUGH_ARGS+=("$1")
            shift
            ;;
        --rebuild-base)
            REBUILD_BASE=true
            PASS_THROUGH_ARGS+=("$1")
            shift
            ;;
        --matrix)
            MATRIX_MODE=true
            shift
            ;;
        --run)
            RUN_MATRIX=true
            shift
            ;;
        --fail-fast)
            FAIL_FAST=true
            shift
            ;;
        --help|-h)
            usage
            ;;
        *)
            echo "Unknown option: $1"
            usage
            ;;
    esac
done

if $MATRIX_MODE; then
    if ! $LIBC_SET; then
        LIBC="all"
    fi
    if ! $JDK_SET; then
        JDK_VERSION="all"
    fi
    if ! $ARCH_SET; then
        ARCH="all"
    fi
    if ! $CONFIG_SET; then
        CONFIG="all"
    fi
fi

# Auto-detect architecture if not specified
if [[ -z "$ARCH" ]]; then
    ARCH=$(detect_arch)
fi

if [[ "$CONTAINER_RUNTIME" != "podman" && "$CONTAINER_RUNTIME" != "docker" ]]; then
    echo "Error: --container must be 'podman' or 'docker'"
    exit 1
fi

if [[ -n "$GTEST_TASK" && -n "$TESTS" ]]; then
    echo "Error: --tests cannot be combined with --gtest-task"
    exit 1
fi

MATRIX_LIBCS_TEXT=$(expand_dimension "$LIBC" "libc" glibc musl)
MATRIX_ARCHES_TEXT=$(expand_dimension "$ARCH" "arch" x64 aarch64)
MATRIX_JDKS_TEXT=$(expand_jdk_dimension "$JDK_VERSION")
MATRIX_CONFIGS_TEXT=$(expand_dimension "$CONFIG" "config" debug release asan tsan)
read_string_into_array MATRIX_LIBCS "$MATRIX_LIBCS_TEXT"
read_string_into_array MATRIX_ARCHES "$MATRIX_ARCHES_TEXT"
read_string_into_array MATRIX_JDKS "$MATRIX_JDKS_TEXT"
read_string_into_array MATRIX_CONFIGS "$MATRIX_CONFIGS_TEXT"
prepare_matrix_cells

if (( MATRIX_RUNNABLE == 0 )); then
    print_matrix_preview
    echo
    echo "Error: matrix has no runnable cells"
    exit 1
fi

if (( MATRIX_TOTAL > 1 || MATRIX_RUNNABLE > 1 || MATRIX_MODE )); then
    if $SHELL_MODE; then
        echo "Error: --shell is interactive and is not supported with matrix runs. Run a single cell without matrix dimensions instead."
        exit 1
    fi
    print_matrix_preview
    if confirm_matrix_run; then
        run_matrix
    fi
    exit 0
fi

if $FAIL_FAST; then
    echo "Error: --fail-fast is only valid when the command expands to a matrix"
    exit 1
fi

if ! command -v "$CONTAINER_RUNTIME" >/dev/null 2>&1; then
    echo "Error: container runtime '$CONTAINER_RUNTIME' not found"
    echo "Use --container to select the runtime, e.g. $0 --container=docker ..."
    exit 1
fi

LIBC="${MATRIX_CELL_LIBCS[0]}"
ARCH="${MATRIX_CELL_ARCHES[0]}"
JDK_VERSION="${MATRIX_CELL_JDKS[0]}"
CONFIG="${MATRIX_CELL_CONFIGS[0]}"

# Parse JDK version and variant (e.g., "21-j9" -> version="21", variant="j9")
JDK_BASE_VERSION="${JDK_VERSION%%-*}"
JDK_VARIANT="${JDK_VERSION#*-}"
if [[ "$JDK_VARIANT" == "$JDK_VERSION" ]]; then
    JDK_VARIANT=""  # No variant specified
fi

# Get JDK URL based on variant and libc
if [[ "$JDK_VARIANT" == "j9" ]]; then
    if [[ "$LIBC" == "musl" ]]; then
        echo "Error: J9/OpenJ9 is not available for musl libc"
        exit 1
    fi
    JDK_URL=$(get_j9_jdk_url "$JDK_BASE_VERSION" "$ARCH")
elif [[ "$JDK_VARIANT" == "graal" ]]; then
    if [[ "$LIBC" == "musl" ]]; then
        echo "Error: GraalVM is not available for musl libc"
        exit 1
    fi
    JDK_URL=$(get_graal_jdk_url "$JDK_BASE_VERSION" "$ARCH")
elif [[ "$LIBC" == "musl" ]]; then
    JDK_URL=$(get_musl_jdk_url "$JDK_BASE_VERSION" "$ARCH")
else
    JDK_URL=$(get_glibc_jdk_url "$JDK_BASE_VERSION" "$ARCH")
fi

if [[ -z "$JDK_URL" ]]; then
    echo "Error: --jdk must be one of: 8, 11, 17, 21, 25, 8-j9, 11-j9, 17-j9, 21-j9, 17-graal, 21-graal, 25-graal"
    exit 1
fi

# Image names for caching
BASE_IMAGE_NAME="${BASE_IMAGE_PREFIX}:${LIBC}-${ARCH}"
IMAGE_NAME="${IMAGE_PREFIX}:${LIBC}-jdk${JDK_VERSION}-${ARCH}"

# Container platform for cross-architecture support
CONTAINER_PLATFORM=""
if [[ "$ARCH" == "aarch64" ]]; then
    CONTAINER_PLATFORM="--platform linux/arm64"
elif [[ "$ARCH" == "x64" ]]; then
    CONTAINER_PLATFORM="--platform linux/amd64"
fi

echo "=== Container Test Runner ==="
echo "LIBC:       $LIBC"
echo "Build JDK:  21 (Gradle 9 requirement)"
echo "Test JDK:   $JDK_VERSION"
echo "Arch:       $ARCH"
echo "Config:     $CONFIG"
echo "Runtime:    $CONTAINER_RUNTIME"
if [[ -n "$GTEST_TASK" ]]; then
    echo "GTest task: $GTEST_TASK"
fi
echo "Tests:      ${TESTS:-<all>}"
echo "GTest:      $(if $GTEST_ENABLED; then echo 'enabled'; else echo 'disabled'; fi)"
echo "Mode:       $(if $SHELL_MODE; then echo 'shell'; else echo 'test'; fi)"
echo "Source:     $(if $MOUNT_MODE; then echo 'mount (local)'; else echo 'clone (clean)'; fi)"
echo "Base Image: $BASE_IMAGE_NAME"
echo "Image:      $IMAGE_NAME"
echo "=========================="

# Create temporary Dockerfile directory
DOCKERFILE_DIR=$(mktemp -d)
trap "rm -rf $DOCKERFILE_DIR" EXIT

# Copy gradle wrapper for caching
cp "$PROJECT_ROOT/gradlew" "$DOCKERFILE_DIR/"
cp -r "$PROJECT_ROOT/gradle" "$DOCKERFILE_DIR/"

# ========== Build Base Image (if needed) ==========
BASE_IMAGE_EXISTS=false
if [[ "$REBUILD" == "false" && "$REBUILD_BASE" == "false" ]]; then
    if "$CONTAINER_RUNTIME" image inspect "$BASE_IMAGE_NAME" >/dev/null 2>&1; then
        BASE_IMAGE_EXISTS=true
        echo ">>> Using cached base image: $BASE_IMAGE_NAME"
    fi
fi

if [[ "$BASE_IMAGE_EXISTS" == "false" ]]; then
    echo ">>> Building base image: $BASE_IMAGE_NAME"

    if [[ "$LIBC" == "musl" ]]; then
        cat > "$DOCKERFILE_DIR/Dockerfile.base" <<'EOF'
FROM alpine:3.21

# Install build dependencies
# - linux-headers provides linux/limits.h
# - compiler-rt provides sanitizer runtimes (ASan, TSan) for clang
# - llvm provides libFuzzer
# - openssh-client for git clone over SSH
RUN apk update && \
    apk add --no-cache \
        curl wget bash make g++ clang git jq cmake coreutils \
        gtest-dev gmock tar binutils musl-dbg linux-headers \
        compiler-rt llvm openssh-client gdb

# Set up Gradle cache directory
ENV GRADLE_USER_HOME=/gradle-cache
RUN mkdir -p /gradle-cache

WORKDIR /workspace
EOF
    else
        # libclang-rt-dev is only available on x64, not arm64
        if [[ "$ARCH" == "x64" ]]; then
            CLANG_RT_PKG="libclang-dev"
        else
            CLANG_RT_PKG=""
        fi
        # On aarch64, install clang-17 + libclang-rt-17-dev from the LLVM apt repository.
        # GCC 11's libtsan only knows 39-bit VMA; the linuxkit kernel (Docker Desktop)
        # uses 48-bit VMA, so GCC 11's TSan crashes with "unexpected memory mapping".
        # Clang-17's compiler-rt TSan runtime handles both 39-bit and 48-bit VMA.
        # libclang-rt-17-dev provides libclang_rt.tsan-aarch64.{a,so} that clang-17
        # needs when linking executables with -fsanitize=thread.
        if [[ "$ARCH" == "aarch64" ]]; then
            CLANG17_BLOCK='
# Install clang-17 + compiler-rt for TSan 48-bit VMA support (aarch64 only)
RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key \
        | gpg --dearmor -o /etc/apt/trusted.gpg.d/llvm.gpg \
    && echo "deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-17 main" \
        > /etc/apt/sources.list.d/llvm.list \
    && apt-get update \
    && apt-get install -y --no-install-recommends clang-17 libclang-rt-17-dev \
    && rm -rf /var/lib/apt/lists/*'
        else
            CLANG17_BLOCK=''
        fi
        cat > "$DOCKERFILE_DIR/Dockerfile.base" <<EOF
FROM ubuntu:22.04

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
# - libasan/libtsan for GCC sanitizers
# - libclang-rt-dev for clang sanitizers and libFuzzer (x64 only)
# - gnupg for LLVM apt key import
# - openssh-client for git clone over SSH
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        curl wget gnupg bash make g++ clang git jq cmake \
        libgtest-dev libgmock-dev tar binutils libc6-dbg \
        ca-certificates linux-libc-dev \
        libasan6 libtsan0 ${CLANG_RT_PKG} openssh-client build-essential gdb && \
    rm -rf /var/lib/apt/lists/*
${CLANG17_BLOCK}

# Set up Gradle cache directory
ENV GRADLE_USER_HOME=/gradle-cache
RUN mkdir -p /gradle-cache

WORKDIR /workspace
EOF
    fi

    "$CONTAINER_RUNTIME" build $CONTAINER_PLATFORM -t "$BASE_IMAGE_NAME" -f "$DOCKERFILE_DIR/Dockerfile.base" "$DOCKERFILE_DIR"
    echo ">>> Base image built: $BASE_IMAGE_NAME"
fi

# ========== Get Build JDK URL (always JDK 21 for Gradle 9) ==========
# Gradle 9 requires JDK 17+ to run; we use JDK 21 (LTS) as the build JDK
BUILD_JDK_VERSION="21"
if [[ "$LIBC" == "musl" ]]; then
    BUILD_JDK_URL=$(get_musl_jdk_url "$BUILD_JDK_VERSION" "$ARCH")
else
    BUILD_JDK_URL=$(get_glibc_jdk_url "$BUILD_JDK_VERSION" "$ARCH")
fi

# ========== Build JDK Image (if needed) ==========
IMAGE_EXISTS=false
if [[ "$REBUILD" == "false" ]]; then
    if "$CONTAINER_RUNTIME" image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
        IMAGE_EXISTS=true
        echo ">>> Using cached image: $IMAGE_NAME"
    fi
fi

if [[ "$IMAGE_EXISTS" == "false" ]]; then
    echo ">>> Building JDK image: $IMAGE_NAME"
    echo ">>> Build JDK (for Gradle): $BUILD_JDK_VERSION"
    echo ">>> Test JDK: $JDK_VERSION"

    # Determine if we need two JDKs or just one
    if [[ "$JDK_BASE_VERSION" == "$BUILD_JDK_VERSION" && -z "$JDK_VARIANT" ]]; then
        # Test JDK is same as build JDK - use single installation
        cat > "$DOCKERFILE_DIR/Dockerfile" <<EOF
FROM $BASE_IMAGE_NAME

# Download and install JDK (used for both build and test)
RUN mkdir -p /jdk && \\
    wget -q "$JDK_URL" -O /tmp/jdk.tar.gz && \\
    tar xzf /tmp/jdk.tar.gz -C /jdk --strip-components=1 && \\
    rm /tmp/jdk.tar.gz

# Set JDK environment (same JDK for build and test)
ENV JAVA_HOME=/jdk
ENV JAVA_TEST_HOME=/jdk
ENV PATH="/jdk/bin:\$PATH"

# Verify JDK installation
RUN java -version

# Pre-cache Gradle wrapper
COPY gradlew /tmp/gradle-setup/
COPY gradle /tmp/gradle-setup/gradle
RUN cd /tmp/gradle-setup && \\
    chmod +x gradlew && \\
    ./gradlew --version && \\
    rm -rf /tmp/gradle-setup

WORKDIR /workspace
EOF
    else
        # Different JDKs for build and test
        cat > "$DOCKERFILE_DIR/Dockerfile" <<EOF
FROM $BASE_IMAGE_NAME

# Download and install Build JDK (JDK $BUILD_JDK_VERSION for Gradle 9)
RUN mkdir -p /jdk-build && \\
    wget -q "$BUILD_JDK_URL" -O /tmp/jdk-build.tar.gz && \\
    tar xzf /tmp/jdk-build.tar.gz -C /jdk-build --strip-components=1 && \\
    rm /tmp/jdk-build.tar.gz

# Download and install Test JDK (JDK $JDK_VERSION)
RUN mkdir -p /jdk-test && \\
    wget -q "$JDK_URL" -O /tmp/jdk-test.tar.gz && \\
    tar xzf /tmp/jdk-test.tar.gz -C /jdk-test --strip-components=1 && \\
    rm /tmp/jdk-test.tar.gz

# Set JDK environment
# JAVA_HOME = Build JDK (for running Gradle)
# JAVA_TEST_HOME = Test JDK (for running tests)
ENV JAVA_HOME=/jdk-build
ENV JAVA_TEST_HOME=/jdk-test
ENV PATH="/jdk-build/bin:\$PATH"

# Verify JDK installations
RUN echo "Build JDK:" && java -version
RUN echo "Test JDK:" && /jdk-test/bin/java -version

# Pre-cache Gradle wrapper
COPY gradlew /tmp/gradle-setup/
COPY gradle /tmp/gradle-setup/gradle
RUN cd /tmp/gradle-setup && \\
    chmod +x gradlew && \\
    ./gradlew --version && \\
    rm -rf /tmp/gradle-setup

WORKDIR /workspace
EOF
    fi

    "$CONTAINER_RUNTIME" build $CONTAINER_PLATFORM -t "$IMAGE_NAME" -f "$DOCKERFILE_DIR/Dockerfile" "$DOCKERFILE_DIR"
    echo ">>> JDK image built: $IMAGE_NAME"
fi

# ========== Run Tests ==========

# Build gradle test command
# Capitalize first letter for gradle task names (testDebug, testAsan, etc.)
# Note: -Ptests property works uniformly across all platforms (glibc, musl, macOS)
CONFIG_CAPITALIZED="$(tr '[:lower:]' '[:upper:]' <<< ${CONFIG:0:1})${CONFIG:1}"
if [[ -n "$GTEST_TASK" ]]; then
    if [[ "$GTEST_TASK" == :* ]]; then
        GRADLE_CMD="./gradlew -PCI -PkeepJFRs $GTEST_TASK"
    else
        GRADLE_CMD="./gradlew -PCI -PkeepJFRs :ddprof-lib:gtest${CONFIG_CAPITALIZED}_${GTEST_TASK}"
    fi
else
    GRADLE_CMD="./gradlew -PCI -PkeepJFRs :ddprof-test:test${CONFIG_CAPITALIZED}"
    if [[ -n "$TESTS" ]]; then
        # No need for quotes around $TESTS - Gradle property values don't require quoting
        GRADLE_CMD="$GRADLE_CMD -Ptests=$TESTS"
    fi
    if ! $GTEST_ENABLED; then
        GRADLE_CMD="$GRADLE_CMD -Pskip-gtest"
    fi
fi
# On aarch64 glibc, TSan needs clang-17's embedded runtime (supports 48-bit VMA).
# GCC 11's libtsan is linked by default but only knows 39-bit VMA, causing a crash.
if [[ "$CONFIG" == "tsan" ]] && [[ "$ARCH" == "aarch64" ]] && [[ "$LIBC" == "glibc" ]]; then
    GRADLE_CMD="$GRADLE_CMD -Pnative.forceCompiler=clang++-17"
fi
GRADLE_CMD="$GRADLE_CMD --no-daemon --parallel --build-cache --no-watch-fs"

# On aarch64 glibc TSan: reduce ASLR entropy so TSan's shadow doesn't conflict with
# initial library load addresses. Requires --privileged for sysctl in the container.
# Do NOT set kernel.randomize_va_space=0: ld-linux-aarch64.so loads at 0x2000000000
# (TSan's shadow start) with full ASLR off.
SYSCTL_PREP=""
NEEDS_PRIVILEGED=false
if [[ "$CONFIG" == "tsan" ]] && [[ "$ARCH" == "aarch64" ]] && [[ "$LIBC" == "glibc" ]]; then
    SYSCTL_PREP="sysctl -w vm.mmap_rnd_bits=28 2>/dev/null || true && "
    NEEDS_PRIVILEGED=true
fi

# Build container run command base
CONTAINER_CMD="$CONTAINER_RUNTIME run --rm"
CONTAINER_VOLUME_RW_OPTIONS=""
CONTAINER_VOLUME_RO_OPTIONS=":ro"
if [[ "${CONTAINER_RUNTIME##*/}" == "podman" ]] && selinux_enforcing; then
    CONTAINER_VOLUME_RW_OPTIONS=":z"
    CONTAINER_VOLUME_RO_OPTIONS=":ro,z"
fi
if $SHELL_MODE; then
    CONTAINER_CMD="$CONTAINER_CMD -it --init --ulimit core=-1 --cap-add=SYS_PTRACE"
fi
if $NEEDS_PRIVILEGED; then
    CONTAINER_CMD="$CONTAINER_CMD --privileged"
fi
CONTAINER_CMD="$CONTAINER_CMD $CONTAINER_PLATFORM"
CONTAINER_CMD="$CONTAINER_CMD -e LIBC=$LIBC"
CONTAINER_CMD="$CONTAINER_CMD -e SANITIZER=$CONFIG"
CONTAINER_CMD="$CONTAINER_CMD -e TEST_CONFIGURATION=$LIBC/${JDK_VERSION}-$CONFIG-$ARCH"
CONTAINER_CMD="$CONTAINER_CMD -e GRADLE_USER_HOME=/gradle-cache"

if $MOUNT_MODE; then
    # Mount mode: use local repo directly (faster, but may have stale artifacts)
    CONTAINER_CMD="$CONTAINER_CMD -v \"$PROJECT_ROOT\":/workspace${CONTAINER_VOLUME_RW_OPTIONS}"
    CONTAINER_CMD="$CONTAINER_CMD $IMAGE_NAME"

    if $SHELL_MODE; then
        SHELL_CMD="/bin/bash"
    else
        SHELL_CMD="${SYSCTL_PREP}${GRADLE_CMD}"
    fi

    echo ""
    echo ">>> Running in container (mount mode)..."
    echo ">>> Command: $SHELL_CMD"
    eval "$CONTAINER_CMD /bin/bash -c '$SHELL_CMD'"
else
    # Clone mode: shallow clone from mounted local repo for clean builds (default)
    # Mount the local repo as source, then clone from it to /workspace
    CONTAINER_CMD="$CONTAINER_CMD -v \"$PROJECT_ROOT\":/source${CONTAINER_VOLUME_RO_OPTIONS}"
    CONTAINER_CMD="$CONTAINER_CMD $IMAGE_NAME"

    # Build clone and test command - clone from local mounted source
    if $SHELL_MODE; then
        CLONE_CMD="git clone --depth 1 file:///source /workspace && cd /workspace && /bin/bash"
    else
        CLONE_CMD="git clone --depth 1 file:///source /workspace && cd /workspace && ${SYSCTL_PREP}${GRADLE_CMD}"
    fi

    echo ""
    echo ">>> Running in container (clone mode)..."
    echo ">>> Cloning from local source to /workspace"
    eval "$CONTAINER_CMD /bin/bash -c '$CLONE_CMD'"
fi
