#!/usr/bin/env bash
# Generate CI test results summary for PR comments
#
# Usage: generate-test-summary.sh <run_id> <output_file>
#
# Fetches job data from GitHub API, parses test results, and generates
# a markdown summary suitable for posting as a PR comment.

set -euo pipefail

RUN_ID="$1"
OUTPUT_FILE="$2"

# --- Configuration ---
REPO="${GITHUB_REPOSITORY:-DataDog/java-profiler}"
SERVER_URL="${GITHUB_SERVER_URL:-https://github.com}"
RUN_URL="${SERVER_URL}/${REPO}/actions/runs/${RUN_ID}"
COMMIT_SHA="${GITHUB_SHA:-unknown}"
SHORT_SHA="${COMMIT_SHA:0:7}"

# --- Helper functions ---
log() {
    echo "[generate-test-summary] $*" >&2
}

# Convert seconds to human-readable duration
format_duration() {
    local seconds=$1
    local hours=$((seconds / 3600))
    local minutes=$(((seconds % 3600) / 60))
    local secs=$((seconds % 60))

    if ((hours > 0)); then
        printf "%dh %dm %ds" "$hours" "$minutes" "$secs"
    elif ((minutes > 0)); then
        printf "%dm %ds" "$minutes" "$secs"
    else
        printf "%ds" "$secs"
    fi
}

# Parse ISO timestamp to epoch seconds
parse_timestamp() {
    local ts="$1"
    if [[ -n "$ts" && "$ts" != "null" ]]; then
        date -j -f "%Y-%m-%dT%H:%M:%SZ" "$ts" "+%s" 2>/dev/null || \
        date -d "$ts" "+%s" 2>/dev/null || \
        echo "0"
    else
        echo "0"
    fi
}

# Get status emoji for job conclusion
status_emoji() {
    case "$1" in
        success)   echo ":white_check_mark:" ;;
        failure)   echo ":x:" ;;
        skipped)   echo ":white_circle:" ;;
        cancelled) echo ":no_entry_sign:" ;;
        *)         echo ":grey_question:" ;;
    esac
}

# --- Fetch job data ---
log "Fetching job data for run $RUN_ID..."
jobs_json=$(gh api "/repos/$REPO/actions/runs/$RUN_ID/jobs" --paginate -q '.jobs')

# --- Parse test jobs ---
log "Parsing test job statuses..."

# Arrays to store parsed data
# Note: Associative arrays need dummy init+unset to work with 'set -u' when empty
declare -A job_status=()
job_status["__init__"]=1; unset 'job_status[__init__]'
declare -A job_url=()
job_url["__init__"]=1; unset 'job_url[__init__]'
declare -A job_duration=()
job_duration["__init__"]=1; unset 'job_duration[__init__]'
declare -a failed_jobs=()
declare -a all_platforms=()
declare -a all_java_versions=()

# Parse each job
while IFS= read -r job; do
    name=$(echo "$job" | jq -r '.name')
    conclusion=$(echo "$job" | jq -r '.conclusion // "pending"')
    html_url=$(echo "$job" | jq -r '.html_url')
    started_at=$(echo "$job" | jq -r '.started_at')
    completed_at=$(echo "$job" | jq -r '.completed_at')

    # Only process test jobs (match pattern: test-linux-{libc}-{arch} ({java}, {config}))
    # Note: regex stored in variable to avoid bash parsing issues with ) character
    # Note: No ^ anchor because reusable workflow jobs are prefixed with caller job name
    #       e.g., "test-matrix / test-linux-glibc-amd64 (8, debug)"
    test_job_pattern='test-linux-([a-z]+)-([a-z0-9]+) \(([^,]+), ([^)]+)\)$'
    if [[ "$name" =~ $test_job_pattern ]]; then
        libc="${BASH_REMATCH[1]}"
        arch="${BASH_REMATCH[2]}"
        java_version="${BASH_REMATCH[3]}"
        config="${BASH_REMATCH[4]}"

        platform="${libc}-${arch}/${config}"

        # Calculate duration
        if [[ -n "$started_at" && "$started_at" != "null" && -n "$completed_at" && "$completed_at" != "null" ]]; then
            start_epoch=$(parse_timestamp "$started_at")
            end_epoch=$(parse_timestamp "$completed_at")
            duration=$((end_epoch - start_epoch))
        else
            duration=0
        fi

        # Store in associative arrays
        key="${platform}|${java_version}"
        job_status["$key"]="$conclusion"
        job_url["$key"]="$html_url"
        job_duration["$key"]="$duration"

        # Track failed jobs
        if [[ "$conclusion" == "failure" ]]; then
            failed_jobs+=("$key")
        fi

        # Collect unique platforms and java versions
        # shellcheck disable=SC2076 # Intentional literal match for array membership
        if [[ ! " ${all_platforms[*]} " =~ " ${platform} " ]]; then
            all_platforms+=("$platform")
        fi
        # shellcheck disable=SC2076 # Intentional literal match for array membership
        if [[ ! " ${all_java_versions[*]} " =~ " ${java_version} " ]]; then
            all_java_versions+=("$java_version")
        fi
    fi
done < <(echo "$jobs_json" | jq -c '.[]')

# Sort java versions (natural sort for versions like 8, 11, 17, 21, 25)
sorted_java=()
if ((${#all_java_versions[@]} > 0)); then
    mapfile -t sorted_java < <(printf '%s\n' "${all_java_versions[@]}" | sort -t'-' -k1,1n -k2,2)
fi

# Sort platforms
sorted_platforms=()
if ((${#all_platforms[@]} > 0)); then
    mapfile -t sorted_platforms < <(printf '%s\n' "${all_platforms[@]}" | sort)
fi

# --- Calculate statistics ---
total_jobs=${#job_status[@]}
passed_jobs=0
failed_count=${#failed_jobs[@]}
skipped_jobs=0
cancelled_jobs=0
total_duration=0
max_duration=0

for key in "${!job_status[@]}"; do
    status="${job_status[$key]}"
    dur="${job_duration[$key]:-0}"

    case "$status" in
        success)   ((++passed_jobs)) ;;
        failure)   ;;  # already counted
        skipped)   ((++skipped_jobs)) ;;
        cancelled) ((++cancelled_jobs)) ;;
    esac

    ((total_duration += dur)) || true
    if ((dur > max_duration)); then
        max_duration=$dur
    fi
done

# --- Download failure artifacts (if any failures) ---
declare -A failure_details=()
failure_details["__init__"]=1; unset 'failure_details[__init__]'

if ((failed_count > 0)); then
    log "Downloading failure artifacts..."
    mkdir -p ./failure-artifacts

    # Try to download test reports
    gh run download "$RUN_ID" --pattern '(test-reports)*' --dir ./failure-artifacts 2>/dev/null || true

    # Parse JUnit XML for failure details
    for key in "${failed_jobs[@]}"; do
        IFS='|' read -r platform java_version <<< "$key"

        # Find matching test report directory
        # Pattern: (test-reports) test-linux-{libc}-{arch} ({java}, {config})
        IFS='/' read -r libc_arch config <<< "$platform"
        report_pattern="./failure-artifacts/*${libc_arch}*${java_version}*${config}*"

        failures=""
        for report_dir in $report_pattern; do
            if [[ -d "$report_dir" ]]; then
                # Parse JUnit XML files
                for xml_file in "$report_dir"/**/TEST-*.xml; do
                    if [[ -f "$xml_file" ]]; then
                        # Extract failed test cases
                        while IFS= read -r testcase; do
                            classname=$(echo "$testcase" | grep -oP 'classname="\K[^"]+' || echo "")
                            testname=$(echo "$testcase" | grep -oP 'name="\K[^"]+' || echo "")
                            # Get failure message (first line only, truncated)
                            failure_msg=$(echo "$testcase" | grep -oP '<failure[^>]*message="\K[^"]*' | head -c 100 || echo "")

                            if [[ -n "$classname" && -n "$testname" ]]; then
                                short_class="${classname##*.}"
                                failures+="| \`${short_class}.${testname}\` | ${failure_msg:-Test failed} |"$'\n'
                            fi
                        done < <(grep -Pzo '(?s)<testcase[^>]*>.*?</testcase>' "$xml_file" 2>/dev/null | tr '\0' '\n' | grep -E '<(failure|error)' || true)
                    fi
                done
            fi
        done

        failure_details["$key"]="$failures"
    done

    # Cleanup
    rm -rf ./failure-artifacts
fi

# --- Generate markdown ---
log "Generating markdown summary..."

{
    echo "## CI Test Results"
    echo ""
    echo "**Run:** [#${RUN_ID}]($RUN_URL) | **Commit:** \`$SHORT_SHA\` | **Duration:** $(format_duration "$max_duration") (longest job)"
    echo ""

    # Overall status
    if ((failed_count == 0)); then
        echo "> :white_check_mark: **All $total_jobs test jobs passed**"
    else
        echo "> :x: **$failed_count of $total_jobs test jobs failed**"
    fi
    echo ""

    # Status matrix table (JDK versions as rows, platforms as columns)
    if ((${#sorted_platforms[@]} > 0 && ${#sorted_java[@]} > 0)); then
        echo "### Status Overview"
        echo ""

        # Header row - platforms as columns
        printf "| JDK |"
        for platform in "${sorted_platforms[@]}"; do
            printf " %s |" "$platform"
        done
        echo ""

        # Separator row
        printf "%s" "|-----|"
        for _ in "${sorted_platforms[@]}"; do
            printf "%s" "--------|"
        done
        echo ""

        # Data rows - JDK versions as rows
        for java in "${sorted_java[@]}"; do
            printf "| %s |" "$java"
            for platform in "${sorted_platforms[@]}"; do
                key="${platform}|${java}"
                status="${job_status[$key]:-}"
                url="${job_url[$key]:-}"

                if [[ -n "$status" ]]; then
                    emoji=$(status_emoji "$status")
                    if [[ -n "$url" ]]; then
                        printf " [%s](%s) |" "$emoji" "$url"
                    else
                        printf " %s |" "$emoji"
                    fi
                else
                    printf " - |"
                fi
            done
            echo ""
        done
        echo ""
        echo "**Legend:** :white_check_mark: passed | :x: failed | :white_circle: skipped | :no_entry_sign: cancelled"
        echo ""
    fi

    # Failed tests details
    if ((failed_count > 0)); then
        echo "### Failed Tests"
        echo ""

        for key in "${failed_jobs[@]}"; do
            IFS='|' read -r platform java_version <<< "$key"
            url="${job_url[$key]:-}"
            details="${failure_details[$key]:-}"

            echo "<details>"
            echo "<summary><b>${platform} / ${java_version}</b></summary>"
            echo ""
            if [[ -n "$url" ]]; then
                echo "**Job:** [View logs]($url)"
                echo ""
            fi

            if [[ -n "$details" ]]; then
                echo "| Test | Error |"
                echo "|------|-------|"
                echo -n "$details"
            else
                echo "_No detailed failure information available. Check the job logs._"
            fi
            echo ""
            echo "</details>"
            echo ""
        done
    fi

    # Summary statistics (single line)
    printf "**Summary:** Total: %d | Passed: %d | Failed: %d" "$total_jobs" "$passed_jobs" "$failed_count"
    if ((skipped_jobs > 0)); then
        printf " | Skipped: %d" "$skipped_jobs"
    fi
    if ((cancelled_jobs > 0)); then
        printf " | Cancelled: %d" "$cancelled_jobs"
    fi
    echo ""
    echo ""

    echo "---"
    echo "*Updated: $(date -u '+%Y-%m-%d %H:%M:%S UTC')*"

} > "$OUTPUT_FILE"

log "Summary written to $OUTPUT_FILE"
log "Total jobs: $total_jobs, Passed: $passed_jobs, Failed: $failed_count"
