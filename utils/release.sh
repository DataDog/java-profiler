#!/usr/bin/env bash

# Copyright 2025, Datadog, Inc

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

# Function to show interactive commit selector
select_commit() {
    local branch=$1

    # Get last 10 commits with format: SHA | DATE | AUTHOR | MESSAGE
    mapfile -t commits < <(git log "$branch" -n 10 --pretty=format:"%H|%ar|%an|%s" 2>&1)

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

            if [ $i -eq $selected ]; then
                echo -e "${GREEN}→ ${short_sha}${NC} ${YELLOW}${date}${NC} ${BLUE}${author:0:20}${NC} ${message:0:60}" >&2
            else
                echo -e "  ${short_sha} ${date} ${author:0:20} ${message:0:60}" >&2
            fi
        done

        echo "" >&2
        echo -e "${BLUE}═══════════════════════════════════════════════════════════════════════════${NC}" >&2
    }

    # Read single keypress from /dev/tty
    read_key() {
        local key
        IFS= read -rsn1 key </dev/tty

        # Handle escape sequences (arrow keys)
        if [[ $key == $'\x1b' ]]; then
            read -rsn2 key </dev/tty
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

# Function to show usage
show_usage() {
    cat << EOF
Usage: $0 <release_type> [options]

Arguments:
  release_type       Type of release: major, minor, or patch

Options:
  --no-dry-run       Actually perform the release (default is dry-run)
  --skip-tests       Skip pre-release tests (emergency releases only)
  --branch <name>    Specify branch to release from (default: current branch)
  --commit <sha>     Specify commit SHA to release (default: interactive selection)
  --help             Show this help message

Examples:
  $0 minor                        # Dry-run, interactive commit selection
  $0 minor --no-dry-run           # Actual minor release
  $0 patch --commit abc123        # Release specific commit
  $0 patch --skip-tests           # Emergency patch without tests (dry-run)
  $0 patch --no-dry-run --skip-tests  # Emergency patch without tests (real)
  $0 major --branch main          # Specify branch explicitly

Release Flow:
  1. Validates inputs and branch rules
  2. Runs pre-release tests (testDebug + testAsan) unless skipped
  3. Creates annotated git tag
  4. Triggers GitLab build pipeline
  5. GitLab publishes to Maven Central
  6. GitHub creates release with assets

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
        print_error "Patch releases can ONLY be performed from 'release/X.Y._' branches"
        echo "Current branch: $BRANCH"
        echo ""
        echo "To create a patch release:"
        echo "  1. Switch to a release branch: git checkout release/X.Y._"
        echo "  2. Run: $0 patch"
        exit 1
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

# Get commit SHA - either from option or interactive selection
# This happens BEFORE gh authentication check so users can browse commits
if [ -z "$COMMIT_SHA" ]; then
    print_info "No commit specified. Showing recent commits on branch: $BRANCH"
    echo ""
    COMMIT_SHA=$(select_commit "$BRANCH")
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
if ! git merge-base --is-ancestor "$COMMIT_SHA" "$BRANCH" 2>&1; then
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
# Check if gh CLI is installed
print_info "Checking GitHub CLI installation..."
if ! command -v gh &> /dev/null; then
    print_error "GitHub CLI (gh) is not installed"
    echo "Install it from: https://cli.github.com/"
    exit 1
fi

# Check if user is authenticated
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

echo ""
print_info "Triggering GitHub Actions workflow..."

# Trigger the workflow
WORKFLOW_OUTPUT=$(mktemp)
WORKFLOW_ERROR=$(mktemp)

if gh workflow run release-validated.yml \
    --ref "$BRANCH" \
    --field release_type="$RELEASE_TYPE" \
    --field dry_run="$DRY_RUN" \
    --field skip_tests="$SKIP_TESTS" > "$WORKFLOW_OUTPUT" 2> "$WORKFLOW_ERROR"; then

    WORKFLOW_SUCCESS=true
    echo ""
    print_success "✓ Workflow triggered successfully!"
    echo ""
    print_info "Monitor the workflow run:"
    echo "  gh run list --workflow=release-validated.yml --limit 1"
    echo ""
    print_info "View workflow logs:"
    echo "  gh run watch"
    echo ""
    print_info "Or view in browser:"
    REPO_URL=$(gh repo view --json url -q .url)
    echo "  ${REPO_URL}/actions/workflows/release-validated.yml"
    echo ""

    if [ "$DRY_RUN" == "false" ]; then
        print_info "Next Steps:"
        echo "  1. Monitor the GitHub Actions workflow"
        echo "  2. GitLab pipeline will build and publish to Maven Central"
        echo "  3. GitHub release will be created automatically"
        echo "  4. Check releases: ${REPO_URL}/releases"
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
    print_success "Status: SUCCESS"
    echo ""
    echo "Next Steps:"
    if [ "$DRY_RUN" == "false" ]; then
        echo "  1. Monitor workflow:  gh run watch"
        echo "  2. Check GitLab:      [Your GitLab pipeline URL]"
        echo "  3. Verify Maven:      https://repo1.maven.org/maven2/com/datadoghq/ddprof/"
        echo "  4. Check release:     ${REPO_URL}/releases"
    else
        echo "  → This was a DRY-RUN. No actual changes were made."
        echo "  → To perform the release, run: $0 $RELEASE_TYPE --no-dry-run --commit $SHORT_SHA"
    fi
else
    print_error "Status: FAILED"
    echo ""
    echo "Error Details:"
    if [ -s "$WORKFLOW_ERROR" ]; then
        cat "$WORKFLOW_ERROR" | sed 's/^/  /'
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
if [ "$WORKFLOW_SUCCESS" = true ]; then
    exit 0
else
    exit 1
fi
