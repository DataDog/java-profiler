#!/usr/bin/env bash

# Copyright 2026, Datadog, Inc

# Script to trigger the Validated Release workflow using GitHub CLI
#
# Usage:
#   ./utils/release.sh <release_type> [options]
#
# Arguments:
#   release_type: major, minor, or patch
#
# Options:
#   --no-dry-run        Actually perform the release (default is dry-run)
#   --skip-tests        Skip pre-release tests (emergency releases only)
#   --branch <name>     Specify branch to release from (default: current branch)
#
# Examples:
#   ./utils/release.sh minor                    # Dry-run of minor release
#   ./utils/release.sh minor --no-dry-run       # Actual minor release
#   ./utils/release.sh patch --skip-tests       # Emergency patch without tests
#   ./utils/release.sh major --branch main      # Specify branch explicitly

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default values
DRY_RUN="true"
SKIP_TESTS="false"
BRANCH=""
RELEASE_TYPE=""
COMMIT_SHA=""
RETRY_RUN_ID=""

# Function to print colored output
print_error() {
    echo -e "${RED}ERROR: $1${NC}" >&2
}

print_success() {
    echo -e "${GREEN}$1${NC}"
}

print_warning() {
    echo -e "${YELLOW}WARNING: $1${NC}"
}

print_info() {
    echo -e "${BLUE}$1${NC}"
}

trap 'echo ""; print_warning "Interrupted"; exit 130' INT

# Read a single keypress (arrow keys, enter, q) from /dev/tty
read_key() {
    local key=""
    if ! IFS= read -rsn1 key </dev/tty; then
        echo "quit"
        return
    fi

    if [[ $key == $'\x1b' ]]; then
        read -rsn2 key </dev/tty || true
        case $key in
            '[A') echo "up" ;;
            '[B') echo "down" ;;
            *) echo "other" ;;
        esac
    elif [[ $key == "" ]]; then
        echo "enter"
    elif [[ $key == "q" ]] || [[ $key == "Q" ]]; then
        echo "quit"
    else
        echo "other"
    fi
}

# Function to show interactive release branch picker (for patch releases)
# Defaults to the most recent branch; older ones are revealed 10 at a time
# via a "show more" row.
select_release_branch() {
    branches=()
    while IFS= read -r line; do
        branches+=("$line")
    done < <(git branch -r --list 'origin/release/[0-9]*.[0-9]*._' \
        | sed 's|[[:space:]]*origin/||' | sort -Vr 2>/dev/null)

    if [ ${#branches[@]} -eq 0 ]; then
        print_error "No release branches found matching release/X.Y._" >&2
        exit 1
    fi

    if [ ! -t 0 ]; then
        print_error "Interactive mode requires a terminal" >&2
        print_error "Use --branch <name> to specify a release branch" >&2
        exit 1
    fi

    local selected=0
    local total=${#branches[@]}
    local page_size=10
    local visible=$(( total < page_size ? total : page_size ))

    display_branch_menu() {
        clear >&2
        echo "" >&2
        echo -e "${BLUE}═══════════════════════════════════════════════════════════════════════════${NC}" >&2
        echo -e "${BLUE}  Select Release Branch for Patch${NC}" >&2
        echo -e "${BLUE}═══════════════════════════════════════════════════════════════════════════${NC}" >&2
        echo "" >&2
        echo "Use ↑/↓ arrow keys to navigate, Enter to select, 'q' to quit" >&2
        echo "" >&2

        for ((i = 0; i < visible; i++)); do
            if [ "$i" -eq "$selected" ]; then
                echo -e "${GREEN}→ ${branches[$i]}${NC}" >&2
            else
                echo -e "  ${branches[$i]}" >&2
            fi
        done

        if [ "$visible" -lt "$total" ]; then
            local remaining=$((total - visible))
            if [ "$selected" -eq "$visible" ]; then
                echo -e "${GREEN}→ … show more ($remaining remaining)${NC}" >&2
            else
                echo -e "  … show more ($remaining remaining)" >&2
            fi
        fi

        echo "" >&2
        echo -e "${BLUE}═══════════════════════════════════════════════════════════════════════════${NC}" >&2
    }

    while true; do
        display_branch_menu
        key=$(read_key)
        local menu_rows=$visible
        [ "$visible" -lt "$total" ] && menu_rows=$((visible + 1))
        case $key in
            up)
                [ $selected -gt 0 ] && selected=$((selected - 1))
                ;;
            down)
                [ $selected -lt $((menu_rows - 1)) ] && selected=$((selected + 1))
                ;;
            enter)
                if [ "$visible" -lt "$total" ] && [ "$selected" -eq "$visible" ]; then
                    visible=$(( visible + page_size < total ? visible + page_size : total ))
                else
                    echo "${branches[$selected]}"
                    return 0
                fi
                ;;
            quit)
                echo "" >&2
                print_info "Selection cancelled" >&2
                exit 0
                ;;
        esac
    done
}

# Function to show interactive commit selector
select_commit() {
    local branch=$1

    # Get last 10 commits with format: SHA | DATE | AUTHOR | MESSAGE
    commits=()
    while IFS= read -r line; do
        commits+=("$line")
    done < <(git log "$branch" -n 10 --pretty=format:"%H|%ar|%an|%s" 2>&1)

    if [ ${#commits[@]} -eq 0 ]; then
        print_error "No commits found on branch $branch" >&2
        exit 1
    fi

    # Check if we're running in a terminal
    if [ ! -t 0 ]; then
        print_error "Interactive mode requires a terminal" >&2
        print_error "Use --commit <sha> to specify a commit" >&2
        exit 1
    fi

    local selected=0
    local total=${#commits[@]}

    # Function to display menu
    display_menu() {
        clear >&2
        echo "" >&2
        echo -e "${BLUE}═══════════════════════════════════════════════════════════════════════════${NC}" >&2
        echo -e "${BLUE}  Select Commit for Release${NC}" >&2
        echo -e "${BLUE}═══════════════════════════════════════════════════════════════════════════${NC}" >&2
        echo "" >&2
        echo "Use ↑/↓ arrow keys to navigate, Enter to select, 'q' to quit" >&2
        echo "" >&2

        for i in "${!commits[@]}"; do
            IFS='|' read -r sha date author message <<< "${commits[$i]}"
            local short_sha="${sha:0:8}"

            if [ "$i" -eq "$selected" ]; then
                echo -e "${GREEN}→ ${short_sha}${NC} ${YELLOW}${date}${NC} ${BLUE}${author:0:20}${NC} ${message:0:60}" >&2
            else
                echo -e "  ${short_sha} ${date} ${author:0:20} ${message:0:60}" >&2
            fi
        done

        echo "" >&2
        echo -e "${BLUE}═══════════════════════════════════════════════════════════════════════════${NC}" >&2
    }

    # Main selection loop
    while true; do
        display_menu

        key=$(read_key)

        case $key in
            up)
                if [ $selected -gt 0 ]; then
                    ((selected--))
                fi
                ;;
            down)
                if [ $selected -lt $((total - 1)) ]; then
                    ((selected++))
                fi
                ;;
            enter)
                IFS='|' read -r sha _ _ _ <<< "${commits[$selected]}"
                echo "$sha"
                return 0
                ;;
            quit)
                echo "" >&2
                print_info "Selection cancelled" >&2
                exit 0
                ;;
        esac
    done
}

# Function to verify GitHub CLI installation, authentication, and repo permissions.
# Sets globals: REPO, REPO_URL, ACTOR.
check_gh_auth() {
    print_info "Checking GitHub CLI installation..."
    if ! command -v gh &> /dev/null; then
        print_error "GitHub CLI (gh) is not installed"
        echo "Install it from: https://cli.github.com/"
        exit 1
    fi

    print_info "Checking GitHub authentication..."
    # Note: gh auth status may return non-zero even when authenticated, so check the output
    AUTH_STATUS=$(gh auth status 2>&1 || true)
    if ! echo "$AUTH_STATUS" | grep -q "Logged in"; then
        print_error "Not authenticated with GitHub CLI"
        echo "Run: gh auth login"
        echo ""
        echo "Current auth status:"
        echo "$AUTH_STATUS"
        exit 1
    fi
    print_info "GitHub authentication verified"

    REPO=$(gh repo view --json nameWithOwner --jq '.nameWithOwner')
    REPO_URL=$(gh repo view --json url --jq '.url')
    VIEWER_PERMISSION=$(gh repo view --json viewerPermission --jq '.viewerPermission')
    case "$VIEWER_PERMISSION" in
        WRITE|MAINTAIN|ADMIN) ;;
        *)
            print_error "Release execution requires write, maintain, or admin access to $REPO"
            exit 1
            ;;
    esac
    ACTOR=$(gh api user --jq '.login')
}

# Function to show usage
show_usage() {
    cat << EOF
Usage: $0 <release_type> [options]
       $0 --retry <run_id>

Arguments:
  release_type       Type of release: major, minor, or patch

Options:
  --no-dry-run       Actually perform the release (default is dry-run)
  --skip-tests       Skip pre-release tests (emergency releases only)
  --branch <name>    Specify branch to release from (default: current branch)
  --commit <sha>     Specify commit SHA to release (default: interactive selection)
  --retry <run_id>   Retry a failed release run by re-dispatching with the same
                     parameters (release_type, dry_run, skip_tests, source_sha)
                     extracted from the original workflow run
  --help             Show this help message

Examples:
  $0 minor                        # Dry-run, interactive commit selection
  $0 minor --no-dry-run           # Actual minor release
  $0 patch                        # Interactive release-branch picker, then commit selection
  $0 patch --branch release/1.2._ # Patch on a specific release branch
  $0 patch --commit abc123        # Release specific commit (branch picked interactively if needed)
  $0 patch --skip-tests           # Emergency patch without tests (dry-run)
  $0 patch --no-dry-run --skip-tests  # Emergency patch without tests (real)
  $0 major --branch main          # Specify branch explicitly
  $0 --retry 33177365160          # Retry failed release run 33177365160

Release Flow:
  1. Validates inputs and branch rules
  2. For patch: optionally backports pending main PRs to the release branch
     first (see utils/prepare-patch.sh), then exits for you to merge the
     backport PR and re-run
  3. Runs pre-release tests (testDebug + testAsan) unless skipped
  4. Creates annotated git tag
  5. Triggers GitLab build pipeline
  6. GitLab publishes to Maven Central
  7. GitHub creates release with assets

Branch Rules:
  - major/minor: Must be run from 'main' branch
  - patch: Must be run from 'release/X.Y._' branch
EOF
}

# Parse arguments first to handle --help
if [ $# -eq 0 ]; then
    print_error "No release type specified"
    show_usage
    exit 1
fi

# Check for --help early
for arg in "$@"; do
    if [ "$arg" == "--help" ]; then
        show_usage
        exit 0
    fi
done

if [[ "$1" == "--retry" ]]; then
    if [ -z "$2" ]; then
        print_error "--retry requires a run ID"
        exit 1
    fi
    RETRY_RUN_ID="$2"
    shift 2

    check_gh_auth

    print_info "Fetching original run $RETRY_RUN_ID..."
    RUN_JSON=$(gh run view "$RETRY_RUN_ID" --repo "$REPO" --json displayTitle,headBranch,headSha 2>&1) || {
        print_error "Could not fetch run $RETRY_RUN_ID"
        echo "$RUN_JSON"
        exit 1
    }

    BRANCH=$(echo "$RUN_JSON" | jq -r '.headBranch')
    COMMIT_SHA=$(echo "$RUN_JSON" | jq -r '.headSha')
    DISPLAY_TITLE=$(echo "$RUN_JSON" | jq -r '.displayTitle')
    SHORT_SHA="${COMMIT_SHA:0:8}"

    # Infer release_type from the display title (the workflow embeds it)
    if echo "$DISPLAY_TITLE" | grep -qi 'major'; then
        RELEASE_TYPE="major"
    elif echo "$DISPLAY_TITLE" | grep -qi 'patch'; then
        RELEASE_TYPE="patch"
    else
        RELEASE_TYPE="minor"
    fi

    # Infer dry_run from the display title
    if echo "$DISPLAY_TITLE" | grep -qi 'dry-run'; then
        DRY_RUN="true"
    else
        DRY_RUN="false"
    fi

    echo ""
    print_info "═══════════════════════════════════════════════════════"
    print_info "  Retry Configuration (from run $RETRY_RUN_ID)"
    print_info "═══════════════════════════════════════════════════════"
    echo "  Release Type: $RELEASE_TYPE (inferred from title)"
    echo "  Branch: $BRANCH"
    echo "  Commit: $SHORT_SHA"
    echo "  Dry Run: $DRY_RUN"
    echo "  Skip Tests: $SKIP_TESTS"
    echo "  Original: $DISPLAY_TITLE"
    print_info "═══════════════════════════════════════════════════════"
    echo ""

    if [ "$DRY_RUN" == "false" ]; then
        print_warning "This will perform an ACTUAL release (retry)!"
        read -p "Are you sure you want to continue? (yes/no): " -r </dev/tty
        if [[ ! $REPLY =~ ^[Yy][Ee][Ss]$ ]]; then
            print_info "Retry cancelled"
            exit 0
        fi
    fi
else

RELEASE_TYPE=$1
shift

while [ $# -gt 0 ]; do
    case "$1" in
        --no-dry-run)
            DRY_RUN="false"
            shift
            ;;
        --skip-tests)
            SKIP_TESTS="true"
            shift
            ;;
        --branch)
            if [ -z "$2" ]; then
                print_error "--branch requires a branch name"
                exit 1
            fi
            BRANCH="$2"
            shift 2
            ;;
        --commit)
            if [ -z "$2" ]; then
                print_error "--commit requires a commit SHA"
                exit 1
            fi
            COMMIT_SHA="$2"
            shift 2
            ;;
        *)
            print_error "Unknown option: $1"
            show_usage
            exit 1
            ;;
    esac
done

goto_trigger=false

if [ "$goto_trigger" != "true" ]; then

# Validate release type
if [[ ! "$RELEASE_TYPE" =~ ^(major|minor|patch)$ ]]; then
    print_error "Invalid release type: $RELEASE_TYPE"
    echo "Must be one of: major, minor, patch"
    exit 1
fi

# Get current branch if not specified
if [ -z "$BRANCH" ]; then
    BRANCH=$(git branch --show-current)
    if [ -z "$BRANCH" ]; then
        print_error "Could not determine current branch"
        echo "Please specify branch with --branch option"
        exit 1
    fi
fi

# Validate branch rules BEFORE commit selection
if [ "$RELEASE_TYPE" == "patch" ]; then
    if [[ ! "$BRANCH" =~ ^release/[0-9]+\.[0-9]+\._$ ]]; then
        print_info "Patch releases require a release branch. Fetching available branches..."
        git fetch --prune origin 'refs/heads/release/*:refs/remotes/origin/release/*' 2>/dev/null || true
        echo ""
        BRANCH=$(select_release_branch)
        clear
        print_info "Branch selected: $BRANCH"
        echo ""
    fi
else
    if [ "$BRANCH" != "main" ]; then
        print_error "Major/minor releases can ONLY be performed from 'main' branch"
        echo "Current branch: $BRANCH"
        echo ""
        echo "To create a $RELEASE_TYPE release:"
        echo "  1. Switch to main: git checkout main"
        echo "  2. Run: $0 $RELEASE_TYPE"
        exit 1
    fi
fi

# Ensure origin/$BRANCH exists, and that a local branch of the same name (if
# one is checked out) isn't stale or carrying unpushed commits, before doing
# any further work.
print_info "Checking that $BRANCH is up to date with origin..."
git fetch --quiet origin "$BRANCH" 2>/dev/null
ORIGIN_BRANCH_HEAD=$(git rev-parse "origin/$BRANCH" 2>&1) || {
    print_error "Branch $BRANCH does not exist on origin"
    exit 1
}
if git show-ref --verify --quiet "refs/heads/$BRANCH"; then
    LOCAL_BRANCH_HEAD=$(git rev-parse "$BRANCH")
    if [ "$LOCAL_BRANCH_HEAD" != "$ORIGIN_BRANCH_HEAD" ]; then
        print_error "Local branch '$BRANCH' is not up to date with origin/$BRANCH"
        echo "  Local:  ${LOCAL_BRANCH_HEAD:0:8}"
        echo "  Origin: ${ORIGIN_BRANCH_HEAD:0:8}"
        echo ""
        echo "Update your local branch, e.g.:"
        echo "  git checkout $BRANCH && git pull --ff-only origin $BRANCH"
        exit 1
    fi
fi
print_info "$BRANCH is up to date with origin"

# For patch releases, offer to backport pending main PRs onto the release
# branch before picking a commit to release.
if [ "$RELEASE_TYPE" == "patch" ]; then
    echo ""
    if [ -t 0 ]; then
        read -p "Pick PRs from main to backport to $BRANCH before releasing? (y/n): " -r </dev/tty
    else
        REPLY="n"
        print_info "No terminal attached; skipping the interactive backport-PR prompt."
    fi
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        PREPARE_ARGS=(--branch "$BRANCH")
        [ "$DRY_RUN" == "false" ] && PREPARE_ARGS+=(--no-dry-run)
        "$(dirname "$0")/prepare-patch.sh" "${PREPARE_ARGS[@]}"
        print_info "Re-run this script once any prep PR has been merged."
        exit 0
    fi
fi

# Get commit SHA - either from option or interactive selection
# This happens BEFORE gh authentication check so users can browse commits
if [ -z "$COMMIT_SHA" ]; then
    print_info "No commit specified. Showing recent commits on branch: $BRANCH"
    echo ""
    COMMIT_SHA=$(select_commit "origin/$BRANCH")
    clear
    print_info "Commit selected. Validating..."
    echo ""
fi

# Validate commit exists
print_info "Validating commit SHA..."
if ! git rev-parse --verify "$COMMIT_SHA" >/dev/null 2>&1; then
    print_error "Invalid commit SHA: $COMMIT_SHA"
    exit 1
fi

# Get full commit SHA
print_info "Resolving full commit SHA..."
COMMIT_SHA=$(git rev-parse "$COMMIT_SHA" 2>&1) || {
    print_error "Failed to resolve commit SHA: $COMMIT_SHA"
    exit 1
}
SHORT_SHA="${COMMIT_SHA:0:8}"
print_info "Commit: $SHORT_SHA"

# Verify the commit is on the selected branch
print_info "Verifying commit is on branch $BRANCH..."
if ! git merge-base --is-ancestor "$COMMIT_SHA" "origin/$BRANCH" 2>&1; then
    print_error "Commit $SHORT_SHA is not on branch '$BRANCH'"
    echo ""
    echo "The selected commit must be part of the branch history."
    echo "Please select a commit that exists on $BRANCH"
    exit 1
fi

# Verify the commit exists on remote
print_info "Verifying commit exists on remote..."
REMOTE_HEAD=$(git rev-parse "origin/$BRANCH" 2>&1) || {
    print_error "Failed to get remote branch HEAD"
    exit 1
}

if [ "$COMMIT_SHA" != "$REMOTE_HEAD" ]; then
    print_warning "Selected commit $SHORT_SHA is not at the HEAD of remote branch origin/$BRANCH"
    echo ""
    echo "The GitHub Actions workflow will run against the remote HEAD:"
    echo "  Remote HEAD: ${REMOTE_HEAD:0:8}"
    echo "  Selected:    $SHORT_SHA"
    echo ""
    print_warning "You need to either:"
    echo "  1. Push your local branch: git push origin $BRANCH"
    echo "  2. Select the remote HEAD commit: ${REMOTE_HEAD:0:8}"
    exit 1
fi

# Get commit info for display
print_info "Retrieving commit information..."
COMMIT_MESSAGE=$(git log -1 --pretty=format:"%s" "$COMMIT_SHA" 2>&1) || {
    print_error "Failed to get commit message"
    exit 1
}
COMMIT_AUTHOR=$(git log -1 --pretty=format:"%an" "$COMMIT_SHA" 2>&1) || {
    print_error "Failed to get commit author"
    exit 1
}
COMMIT_DATE=$(git log -1 --pretty=format:"%ar" "$COMMIT_SHA" 2>&1) || {
    print_error "Failed to get commit date"
    exit 1
}

# NOW check GitHub CLI authentication (after commit selection)
check_gh_auth

# Branch validation already done earlier (before commit selection)

# Show summary
echo ""
print_info "═══════════════════════════════════════════════════════"
print_info "  Release Configuration"
print_info "═══════════════════════════════════════════════════════"
echo "  Release Type: $RELEASE_TYPE"
echo "  Branch: $BRANCH"
echo "  Commit: $SHORT_SHA"
echo "  Message: $COMMIT_MESSAGE"
echo "  Author: $COMMIT_AUTHOR ($COMMIT_DATE)"
echo "  Dry Run: $DRY_RUN"
echo "  Skip Tests: $SKIP_TESTS"
print_info "═══════════════════════════════════════════════════════"
echo ""

if [ "$DRY_RUN" == "false" ]; then
    print_warning "This will perform an ACTUAL release!"
    if [ "$SKIP_TESTS" == "true" ]; then
        print_warning "Tests will be SKIPPED!"
    fi
    echo ""
    read -p "Are you sure you want to continue? (yes/no): " -r </dev/tty
    if [[ ! $REPLY =~ ^[Yy][Ee][Ss]$ ]]; then
        print_info "Release cancelled"
        exit 0
    fi
else
    print_info "Running in DRY-RUN mode (no changes will be made)"
fi

fi  # end of normal-mode block (goto_trigger != true)

fi  # end of else from --retry intercept

echo ""
print_info "Triggering GitHub Actions workflow..."
REQUEST_ID="release-$(date -u +%Y%m%dT%H%M%SZ)-$$-$RANDOM"

# In retry mode, don't pass source_sha — the branch HEAD may have moved since
# the original run, and the workflow rejects SHA mismatches.
#
# This must stay an array. A quoted scalar collapses "--field" and its
# key=value argument into one argv token, which gh rejects with
# "unknown flag: --field source_sha"; an unquoted scalar would silently
# word-split and also emit a stray empty argument in retry mode.
SOURCE_SHA_ARGS=()
if [ -z "$RETRY_RUN_ID" ]; then
    SOURCE_SHA_ARGS=(--field "source_sha=$COMMIT_SHA")
fi

# Trigger the workflow
WORKFLOW_OUTPUT=$(mktemp)
WORKFLOW_ERROR=$(mktemp)

if gh workflow run release-validated.yml \
    --ref "$BRANCH" \
    --field release_type="$RELEASE_TYPE" \
    --field dry_run="$DRY_RUN" \
    --field skip_tests="$SKIP_TESTS" \
    --field request_id="$REQUEST_ID" \
    "${SOURCE_SHA_ARGS[@]}" > "$WORKFLOW_OUTPUT" 2> "$WORKFLOW_ERROR"; then

    WORKFLOW_SUCCESS=true
    echo ""
    print_success "✓ Workflow triggered successfully!"

    # Correlate by an unguessable request ID plus actor, branch, and exact source
    # commit. Never select the merely "latest" release workflow run.
    print_info "Waiting for workflow run to appear..."
    RUN_ID=""
    for i in $(seq 1 15); do
        sleep 2
        RUN_ID=$(gh api "repos/$REPO/actions/runs?event=workflow_dispatch&per_page=50" \
            --jq ".workflow_runs
                | map(select(
                    (.display_title | contains(\"$REQUEST_ID\")) and
                    .actor.login == \"$ACTOR\" and
                    .head_branch == \"$BRANCH\"
                ))
                | if length == 1 then .[0].id else empty end")
        if [ -n "$RUN_ID" ]; then
            break
        fi
    done

    if [ -n "$RUN_ID" ]; then
        echo ""
        print_info "Watching workflow run ${RUN_ID}..."
        echo "  ${REPO_URL}/actions/runs/${RUN_ID}"
        echo ""
        if gh run watch "$RUN_ID" --exit-status; then
            WORKFLOW_CONCLUSION="success"
            print_success "✓ Workflow completed successfully!"
        else
            WORKFLOW_CONCLUSION="failure"
            print_error "✗ Workflow failed!"
            echo "  View logs: gh run view $RUN_ID --log-failed"
        fi
    else
        WORKFLOW_CONCLUSION="unknown"
        print_warning "Could not detect the workflow run. Monitor manually:"
        echo "  gh run list --workflow=release-validated.yml --limit 1"
    fi

    echo ""
    if [ "$DRY_RUN" == "false" ]; then
        print_info "Next Steps:"
        echo "  1. Verify Maven:  https://repo1.maven.org/maven2/com/datadoghq/ddprof/"
        echo "  2. Check release: ${REPO_URL}/releases"
    else
        print_info "This was a dry-run. Review the output and run again with --no-dry-run"
    fi
else
    WORKFLOW_SUCCESS=false
    echo ""
    print_error "Failed to trigger workflow"
fi

# Print comprehensive summary
echo ""
echo ""
print_info "═══════════════════════════════════════════════════════════════════════════"
print_info "  RELEASE EXECUTION SUMMARY"
print_info "═══════════════════════════════════════════════════════════════════════════"
echo ""

# Action performed
echo "Actions Performed:"
echo "  ✓ Validated release type: $RELEASE_TYPE"
echo "  ✓ Validated branch rules: $BRANCH"
echo "  ✓ Selected commit: $SHORT_SHA"

if [ "$WORKFLOW_SUCCESS" = true ]; then
    echo "  ✓ Triggered GitHub Actions workflow"
else
    echo "  ✗ FAILED to trigger GitHub Actions workflow"
fi

echo ""

# Configuration summary
echo "Configuration:"
echo "  Release Type:  $RELEASE_TYPE"
echo "  Branch:        $BRANCH"
echo "  Commit:        $SHORT_SHA ($COMMIT_DATE)"
echo "  Message:       $COMMIT_MESSAGE"
echo "  Author:        $COMMIT_AUTHOR"
echo "  Dry Run:       $DRY_RUN"
echo "  Skip Tests:    $SKIP_TESTS"

echo ""

# Status and next steps
if [ "$WORKFLOW_SUCCESS" = true ]; then
    if [ "${WORKFLOW_CONCLUSION:-}" = "success" ]; then
        print_success "Status: WORKFLOW SUCCEEDED"
    elif [ "${WORKFLOW_CONCLUSION:-}" = "failure" ]; then
        print_error "Status: WORKFLOW FAILED"
        echo "  View logs: gh run view $RUN_ID --log-failed"
    elif [ "$DRY_RUN" == "true" ]; then
        print_success "Status: DRY-RUN COMPLETED"
        echo ""
        echo "  → No actual changes were made."
        echo "  → To perform the release, run: $0 $RELEASE_TYPE --no-dry-run --commit $SHORT_SHA"
    else
        print_warning "Status: WORKFLOW STATUS UNKNOWN"
        echo "  Check manually: gh run list --workflow=release-validated.yml --limit 1"
    fi
else
    print_error "Status: FAILED TO TRIGGER WORKFLOW"
    echo ""
    echo "Error Details:"
    if [ -s "$WORKFLOW_ERROR" ]; then
        sed 's/^/  /' "$WORKFLOW_ERROR"
    else
        echo "  Unknown error. Check GitHub CLI authentication and repository access."
    fi
    echo ""
    echo "Troubleshooting:"
    echo "  • Verify authentication: gh auth status"
    echo "  • Check permissions:     gh repo view --json viewerPermission"
    echo "  • Verify commit exists:  git show $SHORT_SHA"
fi

echo ""
print_info "═══════════════════════════════════════════════════════════════════════════"

# Cleanup temp files
rm -f "$WORKFLOW_OUTPUT" "$WORKFLOW_ERROR"

# Exit with appropriate code
if [ "$WORKFLOW_SUCCESS" = true ] &&
   [ "${WORKFLOW_CONCLUSION:-unknown}" = "success" ]; then
    exit 0
else
    exit 1
fi
