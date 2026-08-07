#!/bin/bash
set -euo pipefail

# Copyright 2026, Datadog, Inc

# Cherry-picks PRs merged to main since a release branch diverged, to prepare
# that branch for its next patch release.
#
# Usage:
#   ./utils/prepare-patch.sh [--branch release/X.Y._] [--no-dry-run]
#
# Flow:
#   1. Select (or take via --branch) the release branch.
#   2. List PRs merged to main after the branch's divergence point.
#   3. Multi-select which PRs to backport.
#   4. Cherry-pick their commits onto a new branch off the release branch.
#   5. Push and open one combined PR against the release branch.

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
PREP_BRANCH=""
CHERRY_PICK_IN_PROGRESS=0
BUILD_FAILED=0

cleanup() {
    local exit_code=$?
    if [ $exit_code -ne 0 ]; then
        if [ $CHERRY_PICK_IN_PROGRESS -eq 1 ]; then
            echo ""
            error "Cherry-pick failed — likely a conflict."
            echo ""
            echo -e "  ${BOLD}Option 1: Resolve manually${RESET}"
            echo -e "    1. Fix the conflicts in the listed files"
            echo -e "    2. ${CYAN}git add <resolved-files>${RESET}"
            echo -e "    3. ${CYAN}git cherry-pick --continue${RESET}"
            echo -e "    4. ${CYAN}git push -u origin $PREP_BRANCH${RESET}"
            echo -e "    5. Create the PR manually or re-run this script"
            echo ""
            echo -e "  ${BOLD}Option 2: Abort and go back${RESET}"
            echo -e "    1. ${CYAN}git cherry-pick --abort${RESET}"
            echo -e "    2. ${CYAN}git checkout $CURRENT_BRANCH${RESET}"
            echo -e "    3. ${CYAN}git branch -D $PREP_BRANCH${RESET}"
            echo ""
            return
        fi
        if [ $BUILD_FAILED -eq 1 ]; then
            echo ""
            error "Build failed after cherry-picking onto $PREP_BRANCH — the selected PRs don't build together."
            echo ""
            echo -e "  ${BOLD}Option 1: Fix and continue${RESET}"
            echo -e "    1. Fix the build on $PREP_BRANCH (currently checked out)"
            echo -e "    2. ${CYAN}./gradlew buildDebug${RESET}"
            echo -e "    3. ${CYAN}git push -u origin $PREP_BRANCH${RESET}"
            echo -e "    4. Create the PR manually or re-run this script"
            echo ""
            echo -e "  ${BOLD}Option 2: Abort and go back${RESET}"
            echo -e "    1. ${CYAN}git checkout $CURRENT_BRANCH${RESET}"
            echo -e "    2. ${CYAN}git branch -D $PREP_BRANCH${RESET}"
            echo ""
            return
        fi
        if [ -n "$CURRENT_BRANCH" ]; then
            warn "Restoring original branch ($CURRENT_BRANCH)"
            git checkout "$CURRENT_BRANCH" 2>/dev/null || true
        fi
    fi
}
trap cleanup EXIT

# --- Argument parsing --------------------------------------------------------
usage() {
    echo -e "${BOLD}Usage:${RESET} $0 [--branch release/X.Y._] [--no-dry-run]"
    echo ""
    echo "  --branch <name>   Release branch to prepare (if omitted, pick from a list)"
    echo "  --no-dry-run      Actually cherry-pick, push, and open the PR (default is dry-run)"
    exit 1
}

RELEASE_BRANCH=""
DRY_RUN=1

while [ $# -gt 0 ]; do
    case "$1" in
        --branch)
            [ -n "${2:-}" ] || usage
            RELEASE_BRANCH="$2"
            shift 2
            ;;
        --no-dry-run) DRY_RUN=0; shift ;;
        --help|-h) usage ;;
        *) usage ;;
    esac
done

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

git fetch --quiet origin
info "Fetched latest from origin"

# --- Read a single keypress (arrow keys, space, enter, a, q) ----------------
read_key() {
    local key
    IFS= read -rsn1 key </dev/tty
    if [[ $key == $'\x1b' ]]; then
        read -rsn2 key </dev/tty
        case $key in
            '[A') echo "up" ;;
            '[B') echo "down" ;;
            *) echo "other" ;;
        esac
    elif [[ $key == "" ]]; then
        echo "enter"
    elif [[ $key == " " ]]; then
        echo "space"
    elif [[ $key == "a" ]] || [[ $key == "A" ]]; then
        echo "all"
    elif [[ $key == "q" ]] || [[ $key == "Q" ]]; then
        echo "quit"
    else
        echo "other"
    fi
}

# --- Release branch selection -------------------------------------------------
select_release_branch() {
    mapfile -t branches < <(git for-each-ref --sort=-version:refname \
        --format='%(refname:short)' 'refs/remotes/origin/release/[0-9]*.[0-9]*._' \
        | sed 's|^origin/||')

    if [ ${#branches[@]} -eq 0 ]; then
        error "No release branches found matching release/X.Y._"
        exit 1
    fi

    if [ ! -t 0 ]; then
        error "Interactive mode requires a terminal"
        error "Use --branch <name> to specify a release branch"
        exit 1
    fi

    local selected=0
    local total=${#branches[@]}
    local page_size=10
    local visible=$(( total < page_size ? total : page_size ))

    display_menu() {
        clear >&2
        echo "" >&2
        echo -e "${CYAN}${BOLD}Select the release branch to prepare${RESET}" >&2
        echo "Use ↑/↓ to navigate, Enter to select, 'q' to quit" >&2
        echo "" >&2
        for ((i = 0; i < visible; i++)); do
            if [ "$i" -eq "$selected" ]; then
                echo -e "${GREEN}→ ${branches[$i]}${RESET}" >&2
            else
                echo -e "  ${branches[$i]}" >&2
            fi
        done
        if [ "$visible" -lt "$total" ]; then
            local remaining=$((total - visible))
            if [ "$selected" -eq "$visible" ]; then
                echo -e "${GREEN}→ … show more ($remaining remaining)${RESET}" >&2
            else
                echo -e "  … show more ($remaining remaining)" >&2
            fi
        fi
        echo "" >&2
    }

    while true; do
        display_menu
        key=$(read_key)
        local menu_rows=$visible
        [ "$visible" -lt "$total" ] && menu_rows=$((visible + 1))
        case $key in
            up)   [ $selected -gt 0 ] && ((selected--)) ;;
            down) [ $selected -lt $((menu_rows - 1)) ] && ((selected++)) ;;
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
                info "Selection cancelled"
                exit 0
                ;;
        esac
    done
}

if [ -z "$RELEASE_BRANCH" ]; then
    step "Select a release branch"
    RELEASE_BRANCH=$(select_release_branch)
    clear
fi

git show-ref --verify --quiet "refs/remotes/origin/$RELEASE_BRANCH" 2>/dev/null || {
    error "Branch $RELEASE_BRANCH does not exist on origin"
    exit 1
}
info "Target branch: $RELEASE_BRANCH"

# --- Find PRs merged to main after the branch diverged -----------------------
step "Looking for PRs merged to main since $RELEASE_BRANCH diverged"

mapfile -t CANDIDATE_SHAS < <(git rev-list --reverse "origin/main" "^origin/$RELEASE_BRANCH")

if [ ${#CANDIDATE_SHAS[@]} -eq 0 ]; then
    info "No commits on main ahead of $RELEASE_BRANCH. Nothing to prepare."
    exit 0
fi

MERGED_PRS_JSON=$(gh pr list --base main --state merged --limit 200 \
    --json number,title,mergedAt,mergeCommit,labels)

CANDIDATE_SET=$(printf '%s\n' "${CANDIDATE_SHAS[@]}" | jq -R -s 'split("\n") | map(select(length > 0))')

PR_LIST_JSON=$(jq -n --argjson prs "$MERGED_PRS_JSON" --argjson shas "$CANDIDATE_SET" '
    $prs
    | map(select(.mergeCommit.oid as $c | $shas | index($c) != null))
    | sort_by(.mergedAt)
')

PR_COUNT=$(echo "$PR_LIST_JSON" | jq 'length')
if [ "$PR_COUNT" -eq 0 ]; then
    info "No merged PRs found ahead of $RELEASE_BRANCH. Nothing to prepare."
    exit 0
fi

mapfile -t PR_NUMBERS < <(echo "$PR_LIST_JSON" | jq -r '.[].number')
mapfile -t PR_TITLES < <(echo "$PR_LIST_JSON" | jq -r '.[].title')
mapfile -t PR_LABELS < <(echo "$PR_LIST_JSON" | jq -r '[.[].labels | map(.name) | join(",")][]')

info "Found $PR_COUNT candidate PR(s)"

# --- Multi-select PR picker ---------------------------------------------------
select_prs() {
    local total=${#PR_NUMBERS[@]}
    local -a checked
    for ((i = 0; i < total; i++)); do checked[i]=0; done
    local cursor=0

    if [ ! -t 0 ]; then
        error "Interactive mode requires a terminal"
        exit 1
    fi

    display_menu() {
        clear >&2
        echo "" >&2
        echo -e "${CYAN}${BOLD}Select PRs to backport to $RELEASE_BRANCH${RESET}" >&2
        echo "↑/↓ navigate, Space toggle, 'a' toggle all, Enter confirm, 'q' cancel" >&2
        echo "" >&2
        for i in "${!PR_NUMBERS[@]}"; do
            local box="[ ]"
            [ "${checked[$i]}" -eq 1 ] && box="[x]"
            local line="${box} #${PR_NUMBERS[$i]}  ${PR_TITLES[$i]:0:60}"
            [ -n "${PR_LABELS[$i]}" ] && line="$line  (${PR_LABELS[$i]})"
            if [ "$i" -eq "$cursor" ]; then
                echo -e "${GREEN}→ ${line}${RESET}" >&2
            else
                echo -e "  ${line}" >&2
            fi
        done
        echo "" >&2
    }

    while true; do
        display_menu
        key=$(read_key)
        case $key in
            up)   [ $cursor -gt 0 ] && ((cursor--)) ;;
            down) [ $cursor -lt $((total - 1)) ] && ((cursor++)) ;;
            space)
                [ "${checked[$cursor]}" -eq 1 ] && checked[cursor]=0 || checked[cursor]=1
                ;;
            all)
                local any_unchecked=0
                for ((i = 0; i < total; i++)); do
                    [ "${checked[$i]}" -eq 0 ] && any_unchecked=1
                done
                for ((i = 0; i < total; i++)); do checked[i]=$any_unchecked; done
                ;;
            enter)
                local out=()
                for ((i = 0; i < total; i++)); do
                    [ "${checked[$i]}" -eq 1 ] && out+=("$i")
                done
                printf '%s\n' "${out[@]}"
                return 0
                ;;
            quit)
                echo "" >&2
                info "Selection cancelled"
                exit 0
                ;;
        esac
    done
}

mapfile -t SELECTED_IDX < <(select_prs)
clear

if [ ${#SELECTED_IDX[@]} -eq 0 ]; then
    warn "No PRs selected. Nothing to do."
    exit 0
fi

echo ""
step "Selected PR(s):"
for idx in "${SELECTED_IDX[@]}"; do
    echo -e "  #${PR_NUMBERS[$idx]}  ${PR_TITLES[$idx]}"
done
echo ""

# --- Dry-run summary -----------------------------------------------------
PREP_BRANCH="$USER/patch-prep-${RELEASE_BRANCH#release/}"

if [ $DRY_RUN -eq 1 ]; then
    step "Dry-run summary (no changes will be made)"
    echo ""
    echo -e "  Target:  ${BOLD}$RELEASE_BRANCH${RESET}"
    echo -e "  Branch:  ${BOLD}$PREP_BRANCH${RESET}"
    echo -e "  PRs:     ${#SELECTED_IDX[@]}"
    for idx in "${SELECTED_IDX[@]}"; do
        echo "           #${PR_NUMBERS[$idx]} — ${PR_TITLES[$idx]}"
    done
    echo ""
    info "Dry run complete. Re-run without --dry-run to execute."
    exit 0
fi

# --- Handle existing prep branch ----------------------------------------------
if git show-ref --verify --quiet "refs/remotes/origin/$PREP_BRANCH" 2>/dev/null; then
    error "Remote branch $PREP_BRANCH already exists. Delete it or finish that prep first."
    exit 1
fi
if git show-ref --verify --quiet "refs/heads/$PREP_BRANCH" 2>/dev/null; then
    warn "Local branch $PREP_BRANCH already exists."
    echo -n "Delete it and start fresh? (y/n) "
    read -r ANSWER
    [ "$ANSWER" == "y" ] || { echo "Aborting."; exit 1; }
    git branch -D "$PREP_BRANCH"
fi

# --- Cherry-pick selected PRs --------------------------------------------------
step "Creating $PREP_BRANCH from $RELEASE_BRANCH"

git checkout "$RELEASE_BRANCH"
git pull --quiet
git checkout -b "$PREP_BRANCH"

CHERRY_PICK_IN_PROGRESS=1
for idx in "${SELECTED_IDX[@]}"; do
    num="${PR_NUMBERS[$idx]}"
    step "Cherry-picking #$num"

    PR_DATA=$(gh pr view "$num" --json commits,mergeCommit)
    PR_COMMITS=$(echo "$PR_DATA" | jq -r '.commits[].oid')
    PR_MERGE_COMMIT=$(echo "$PR_DATA" | jq -r '.mergeCommit.oid // empty')

    USE_MERGE_COMMIT=0
    for PR_COMMIT in $PR_COMMITS; do
        if ! git cat-file -e "$PR_COMMIT" 2>/dev/null; then
            USE_MERGE_COMMIT=1
            break
        fi
        PARENT_COUNT=$(git rev-list --parents -n 1 "$PR_COMMIT" 2>/dev/null | wc -w)
        if [ "$PARENT_COUNT" -gt 2 ]; then
            USE_MERGE_COMMIT=1
            break
        fi
    done

    if [ $USE_MERGE_COMMIT -eq 1 ]; then
        [ -n "$PR_MERGE_COMMIT" ] || { error "No usable commit found for #$num"; exit 1; }
        PR_COMMITS="$PR_MERGE_COMMIT"
    fi

    for PR_COMMIT in $PR_COMMITS; do
        git cherry-pick -x "$PR_COMMIT"
    done
done
CHERRY_PICK_IN_PROGRESS=0

step "Validating build (the selected PRs may not build together)"
if ! ./gradlew buildDebug --console=plain; then
    BUILD_FAILED=1
    exit 1
fi
info "Build validation passed"

git push -u origin "$PREP_BRANCH"
info "Pushed $PREP_BRANCH"

# --- Create combined PR --------------------------------------------------
step "Creating pull request"

BODY="Backports the following PR(s) to \`$RELEASE_BRANCH\` in preparation for the next patch release:"$'\n\n'
for idx in "${SELECTED_IDX[@]}"; do
    BODY+="- #${PR_NUMBERS[$idx]} — ${PR_TITLES[$idx]}"$'\n'
done

PREP_PR_URL=$(gh pr create --base "$RELEASE_BRANCH" \
    --head "$PREP_BRANCH" \
    --title "🍒 Prepare patch: backport ${#SELECTED_IDX[@]} PR(s) to $RELEASE_BRANCH" \
    --body "$BODY")
[ -n "$PREP_PR_URL" ] || { error "gh pr create did not return a URL"; exit 1; }
info "Created: $PREP_PR_URL"

for idx in "${SELECTED_IDX[@]}"; do
    gh pr comment "${PR_NUMBERS[$idx]}" --body "Backported to \`$RELEASE_BRANCH\` via $PREP_PR_URL" 2>/dev/null || true
done

# --- Restore ------------------------------------------------------------------
step "Restoring original branch"
git checkout "$CURRENT_BRANCH"
info "Back on $CURRENT_BRANCH"

echo ""
echo -e "${GREEN}${BOLD}Done!${RESET}"
echo -e "  ${BOLD}Prep PR:${RESET} $PREP_PR_URL"
echo ""
info "Once merged, re-run ./utils/release.sh patch --branch $RELEASE_BRANCH"
