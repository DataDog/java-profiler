#!/bin/bash
set -euo pipefail

# --- Colors & helpers --------------------------------------------------------
if [ -t 1 ]; then
    RED='\033[0;31m'; GREEN='\033[0;32m'; YELLOW='\033[0;33m'
    CYAN='\033[0;36m'; BOLD='\033[1m'; RESET='\033[0m'
else
    RED=''; GREEN=''; YELLOW=''; CYAN=''; BOLD=''; RESET=''
fi
info()  { echo -e "${GREEN}✓${RESET} $*"; }
warn()  { echo -e "${YELLOW}⚠${RESET} $*"; }
error() { echo -e "${RED}✗${RESET} $*" >&2; }
step()  { echo -e "${CYAN}→${RESET} ${BOLD}$*${RESET}"; }

# --- Cleanup trap ------------------------------------------------------------
CURRENT_BRANCH=""
BACKPORT_BRANCH=""
CHERRY_PICK_IN_PROGRESS=0
DRY_RUN=0

cleanup() {
    local exit_code=$?
    if [ $exit_code -ne 0 ]; then
        if [ $CHERRY_PICK_IN_PROGRESS -eq 1 ]; then
            echo ""
            error "Cherry-pick failed — likely a conflict."
            echo ""
            echo -e "  You have two options:"
            echo ""
            echo -e "  ${BOLD}Option 1: Resolve manually${RESET}"
            echo -e "    1. Fix the conflicts in the listed files"
            echo -e "    2. ${CYAN}git add <resolved-files>${RESET}"
            echo -e "    3. ${CYAN}git cherry-pick --continue${RESET}"
            echo -e "    4. ${CYAN}git push -u origin $BACKPORT_BRANCH${RESET}"
            echo -e "    5. Create the PR manually or re-run this script"
            echo ""
            echo -e "  ${BOLD}Option 2: Abort and go back${RESET}"
            echo -e "    1. ${CYAN}git cherry-pick --abort${RESET}"
            echo -e "    2. ${CYAN}git checkout $CURRENT_BRANCH${RESET}"
            echo -e "    3. ${CYAN}git branch -D $BACKPORT_BRANCH${RESET}"
            echo ""
            return
        fi
        # Generic failure — try to restore original branch
        if [ -n "$CURRENT_BRANCH" ]; then
            warn "Restoring original branch ($CURRENT_BRANCH)"
            git checkout "$CURRENT_BRANCH" 2>/dev/null || true
        fi
    fi
}
trap cleanup EXIT

# --- Argument parsing --------------------------------------------------------
usage() {
    echo -e "${BOLD}Usage:${RESET} $0 [--dry-run] [<release-name>] <pr-number-or-url>"
    echo ""
    echo "  <release-name>     e.g. 1.9._ (if omitted, you'll pick from a list)"
    echo "  <pr-number-or-url> PR number (420) or full URL (https://github.com/.../pull/420)"
    echo "  --dry-run          Show what would happen without making changes"
    exit 1
}

RELEASE_NAME=""
PR_INPUT=""

for arg in "$@"; do
    case "$arg" in
        --dry-run) DRY_RUN=1 ;;
        --help|-h) usage ;;
        *)
            if [ -z "$PR_INPUT" ] && [[ "$arg" =~ (^[0-9]+$|/pull/[0-9]+) ]]; then
                PR_INPUT="$arg"
            elif [ -z "$RELEASE_NAME" ]; then
                RELEASE_NAME="$arg"
            elif [ -z "$PR_INPUT" ]; then
                PR_INPUT="$arg"
            else
                usage
            fi
            ;;
    esac
done

if [ -z "$PR_INPUT" ]; then
    usage
fi

# Extract PR number from URL or plain number
if [[ "$PR_INPUT" =~ /pull/([0-9]+) ]]; then
    PR_NUMBER="${BASH_REMATCH[1]}"
elif [[ "$PR_INPUT" =~ ^[0-9]+$ ]]; then
    PR_NUMBER="$PR_INPUT"
else
    error "Cannot parse PR number from: $PR_INPUT"
    exit 1
fi

# --- Check requirements ------------------------------------------------------
step "Checking prerequisites"

CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)

for cmd in gh jq; do
    $cmd --version 1>/dev/null 2>&1 || { error "$cmd is not installed"; exit 1; }
done
info "gh and jq are available"

if [ -n "$(git status --porcelain)" ]; then
    error "Working tree is not clean. Please stash or commit your changes first."
    exit 1
fi
info "Working tree is clean"

git fetch --quiet
info "Fetched latest from origin"

# --- Release branch selection ------------------------------------------------
if [ -z "$RELEASE_NAME" ]; then
    step "Select a release branch"
    BRANCHES=()
    while IFS= read -r ref; do
        branch="${ref#refs/remotes/origin/release/}"
        BRANCHES+=("$branch")
    done < <(git for-each-ref --sort=-version:refname --format='%(refname)' 'refs/remotes/origin/release/*')

    if [ ${#BRANCHES[@]} -eq 0 ]; then
        error "No release branches found"
        exit 1
    fi

    # Show the 10 most recent
    SHOW_COUNT=10
    if [ ${#BRANCHES[@]} -lt $SHOW_COUNT ]; then
        SHOW_COUNT=${#BRANCHES[@]}
    fi
    echo ""
    for i in $(seq 1 "$SHOW_COUNT"); do
        echo -e "  ${BOLD}$i)${RESET} release/${BRANCHES[$((i-1))]}"
    done
    echo ""
    echo -n "Pick a branch [1-$SHOW_COUNT]: "
    read -r PICK
    if ! [[ "$PICK" =~ ^[0-9]+$ ]] || [ "$PICK" -lt 1 ] || [ "$PICK" -gt "$SHOW_COUNT" ]; then
        error "Invalid selection"
        exit 1
    fi
    RELEASE_NAME="${BRANCHES[$((PICK-1))]}"
fi

if [[ ! "$RELEASE_NAME" =~ ^[0-9]+\.[0-9]+\._ ]]; then
    error "Release name should be in the format X.Y._ (e.g. 1.9._)"
    exit 1
fi

RELEASE_BRANCH="release/$RELEASE_NAME"
git show-ref --verify --quiet "refs/remotes/origin/$RELEASE_BRANCH" 2>/dev/null || {
    error "Branch $RELEASE_BRANCH does not exist on origin"
    exit 1
}
info "Target branch: $RELEASE_BRANCH"

# --- Fetch PR details (single API call) --------------------------------------
step "Fetching PR #$PR_NUMBER details"

PR_DATA=$(gh pr view "$PR_NUMBER" --json commits,mergeCommit,title,labels,state)
PR_STATE=$(echo "$PR_DATA" | jq -r '.state')
if [ "$PR_STATE" == "null" ] || [ -z "$PR_STATE" ]; then
    error "PR #$PR_NUMBER does not exist"
    exit 1
fi
if [ "$PR_STATE" != "MERGED" ]; then
    warn "PR #$PR_NUMBER is $PR_STATE (not merged). Proceed anyway? (y/n)"
    read -r ANSWER
    [ "$ANSWER" == "y" ] || { echo "Aborting."; exit 1; }
fi

PR_TITLE=$(echo "$PR_DATA" | jq -r '.title')
PR_LABELS=$(echo "$PR_DATA" | jq -r '[.labels[].name] | join(",")')
PR_COMMITS=$(echo "$PR_DATA" | jq -r '.commits[].oid')
PR_MERGE_COMMIT=$(echo "$PR_DATA" | jq -r '.mergeCommit.oid // empty')

info "PR: $PR_TITLE"

# --- Determine commits to cherry-pick ----------------------------------------
USE_MERGE_COMMIT=0

for PR_COMMIT in $PR_COMMITS; do
    if ! git cat-file -e "$PR_COMMIT" 2>/dev/null; then
        warn "Commit $PR_COMMIT is no longer present (garbage collected after squash)."
        USE_MERGE_COMMIT=1
        break
    fi
done

if [ $USE_MERGE_COMMIT -eq 0 ]; then
    for PR_COMMIT in $PR_COMMITS; do
        PARENT_COUNT=$(git rev-list --parents -n 1 "$PR_COMMIT" 2>/dev/null | wc -w)
        if [ "$PARENT_COUNT" -gt 2 ]; then
            warn "PR contains a merge commit ($PR_COMMIT)."
            USE_MERGE_COMMIT=1
            break
        fi
    done
fi

if [ $USE_MERGE_COMMIT -eq 1 ]; then
    if [ -z "$PR_MERGE_COMMIT" ]; then
        error "Need merge commit but PR has not been merged yet."
        exit 1
    fi
    echo -n "Cherry-pick the merge commit instead of individual commits? (y/n) "
    read -r ANSWER
    if [ "$ANSWER" == "y" ]; then
        PR_COMMITS="$PR_MERGE_COMMIT"
    else
        echo "Aborting. Please backport manually."
        exit 1
    fi
fi

COMMIT_COUNT=$(echo "$PR_COMMITS" | wc -w | tr -d ' ')
info "Will cherry-pick $COMMIT_COUNT commit(s)"

# --- Handle existing backport branch -----------------------------------------
BACKPORT_BRANCH="$USER/backport-pr-$PR_NUMBER"
if git show-ref --verify --quiet "refs/remotes/origin/$BACKPORT_BRANCH" 2>/dev/null; then
    warn "Remote branch $BACKPORT_BRANCH already exists."
    echo -n "Delete it and start fresh? (y/n) "
    read -r ANSWER
    if [ "$ANSWER" == "y" ]; then
        if [ $DRY_RUN -eq 0 ]; then
            git push origin --delete "$BACKPORT_BRANCH" 2>/dev/null || true
        fi
        info "Deleted remote branch $BACKPORT_BRANCH"
    else
        echo "Aborting."
        exit 1
    fi
fi
if git show-ref --verify --quiet "refs/heads/$BACKPORT_BRANCH" 2>/dev/null; then
    warn "Local branch $BACKPORT_BRANCH already exists."
    echo -n "Delete it and start fresh? (y/n) "
    read -r ANSWER
    if [ "$ANSWER" == "y" ]; then
        if [ $DRY_RUN -eq 0 ]; then
            git branch -D "$BACKPORT_BRANCH"
        fi
        info "Deleted local branch $BACKPORT_BRANCH"
    else
        echo "Aborting."
        exit 1
    fi
fi

# --- Dry-run summary ---------------------------------------------------------
if [ $DRY_RUN -eq 1 ]; then
    echo ""
    step "Dry-run summary (no changes will be made)"
    echo ""
    echo -e "  PR:        ${BOLD}#$PR_NUMBER${RESET} — $PR_TITLE"
    echo -e "  Target:    ${BOLD}$RELEASE_BRANCH${RESET}"
    echo -e "  Branch:    ${BOLD}$BACKPORT_BRANCH${RESET}"
    echo -e "  Commits:   $COMMIT_COUNT"
    for c in $PR_COMMITS; do
        echo -e "             $c"
    done
    echo -e "  Labels:    ${PR_LABELS:-<none>}"
    echo -e "  PR title:  🍒 $PR_NUMBER - $PR_TITLE"
    echo ""
    info "Dry run complete. Re-run without --dry-run to execute."
    exit 0
fi

# --- Backport ----------------------------------------------------------------
step "Creating backport"

git checkout "$RELEASE_BRANCH"
git pull --quiet
git checkout -b "$BACKPORT_BRANCH"

CHERRY_PICK_IN_PROGRESS=1
for PR_COMMIT in $PR_COMMITS; do
    git cherry-pick -x "$PR_COMMIT"
done
CHERRY_PICK_IN_PROGRESS=0

git push -u origin "$BACKPORT_BRANCH"
info "Pushed $BACKPORT_BRANCH"

# --- Create PR ---------------------------------------------------------------
step "Creating pull request"

LABEL_ARGS=""
if [ -n "$PR_LABELS" ]; then
    LABEL_ARGS="--label $PR_LABELS"
fi

# shellcheck disable=SC2086
BACKPORT_PR_URL=$(gh pr create --base "$RELEASE_BRANCH" \
    --head "$BACKPORT_BRANCH" \
    --title "🍒 $PR_NUMBER - $PR_TITLE" \
    --body "Backport of #$PR_NUMBER to \`$RELEASE_BRANCH\`" \
    $LABEL_ARGS 2>&1)
info "Created: $BACKPORT_PR_URL"

# Comment on the original PR for traceability
gh pr comment "$PR_NUMBER" --body "Backported to \`$RELEASE_BRANCH\` via $BACKPORT_PR_URL" 2>/dev/null || true

# --- Restore ------------------------------------------------------------------
step "Restoring original branch"
git checkout "$CURRENT_BRANCH"
info "Back on $CURRENT_BRANCH"

echo ""
echo -e "${GREEN}${BOLD}Done!${RESET} Backport PR: $BACKPORT_PR_URL"
