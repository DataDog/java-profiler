#!/usr/bin/env bash

set -euo pipefail

LABEL="trivial"
MODE="pr"
FIXTURE=""
REPO="DataDog/java-profiler"
PR_NUMBER=""
SENDER=""
BASE=""
HEAD=""
SOURCE_SHA=""
EXPECTED_HEAD_SHA=""
TEMP_DIR=""

die() {
  echo "release-bump validation failed: $*" >&2
  exit 1
}

cleanup() {
  if [ -n "$TEMP_DIR" ] && [ -d "$TEMP_DIR" ]; then
    rm -rf "$TEMP_DIR"
  fi
}
trap cleanup EXIT

while [ "$#" -gt 0 ]; do
  case "$1" in
    --fixture) FIXTURE=${2:-}; shift 2 ;;
    --repo) REPO=${2:-}; shift 2 ;;
    --pr-number) PR_NUMBER=${2:-}; shift 2 ;;
    --sender) SENDER=${2:-}; shift 2 ;;
    --branch) MODE="branch"; shift ;;
    --base) BASE=${2:-}; shift 2 ;;
    --head) HEAD=${2:-}; shift 2 ;;
    --source-sha) SOURCE_SHA=${2:-}; shift 2 ;;
    --expected-head-sha) EXPECTED_HEAD_SHA=${2:-}; shift 2 ;;
    *) die "unknown argument: $1" ;;
  esac
done

command -v jq >/dev/null || die "jq is required"
TEMP_DIR=$(mktemp -d)
DATA="$TEMP_DIR/data.json"
PARENT_BUILD="$TEMP_DIR/parent-build.gradle.kts"
HEAD_BUILD="$TEMP_DIR/head-build.gradle.kts"

permission() {
  gh api "repos/$REPO/collaborators/$1/permission" --jq '.permission'
}

content() {
  gh api -H "Accept: application/vnd.github.raw+json" \
    "repos/$REPO/contents/build.gradle.kts?ref=$1"
}

is_reachable() {
  local status
  status=$(gh api "repos/$REPO/compare/$1...$2" --jq '.status')
  [ "$status" = "ahead" ] || [ "$status" = "identical" ]
}

if [ -n "$FIXTURE" ]; then
  [ -f "$FIXTURE" ] || die "fixture does not exist: $FIXTURE"
  jq 'del(.parent_build, .head_build)' "$FIXTURE" > "$DATA"
  jq -j '.parent_build' "$FIXTURE" > "$PARENT_BUILD"
  jq -j '.head_build' "$FIXTURE" > "$HEAD_BUILD"
elif [ "$MODE" = "pr" ]; then
  if [ -z "$PR_NUMBER" ] || [ -z "$SENDER" ]; then
    die "PR validation requires --pr-number and --sender"
  fi
  [[ "$PR_NUMBER" =~ ^[0-9]+$ ]] || die "invalid PR number"

  PR=$(gh api "repos/$REPO/pulls/$PR_NUMBER")
  AUTHOR=$(jq -er '.user.login' <<<"$PR")
  HEAD_SHA=$(jq -er '.head.sha' <<<"$PR")
  COMMIT=$(gh api "repos/$REPO/commits/$HEAD_SHA")
  PARENTS=$(jq -c '[.parents[].sha]' <<<"$COMMIT")
  PARENT_SHA=$(jq -r 'if length == 1 then .[0] else "" end' <<<"$PARENTS")
  FILES=$(gh api --paginate "repos/$REPO/pulls/$PR_NUMBER/files?per_page=100" \
    --slurp --jq 'add | map({filename, status})')
  CURRENT_HEAD_SHA=$(gh api "repos/$REPO/pulls/$PR_NUMBER" --jq '.head.sha')
  SENDER_PERMISSION=$(permission "$SENDER")
  AUTHOR_PERMISSION=$(permission "$AUTHOR")
  PARENT_REACHABLE=false
  if [ -n "$PARENT_SHA" ] &&
     is_reachable "$PARENT_SHA" "$(jq -er '.base.sha' <<<"$PR")"; then
    PARENT_REACHABLE=true
    content "$PARENT_SHA" > "$PARENT_BUILD"
  else
    : > "$PARENT_BUILD"
  fi
  content "$HEAD_SHA" > "$HEAD_BUILD"

  jq -n \
    --arg repo "$REPO" \
    --arg sender_permission "$SENDER_PERMISSION" \
    --arg author_login "$AUTHOR" \
    --arg author_type "$(jq -er '.user.type' <<<"$PR")" \
    --arg author_permission "$AUTHOR_PERMISSION" \
    --arg state "$(jq -er '.state' <<<"$PR")" \
    --argjson draft "$(jq -e '.draft' <<<"$PR")" \
    --arg title "$(jq -er '.title' <<<"$PR")" \
    --arg base_ref "$(jq -er '.base.ref' <<<"$PR")" \
    --arg base_sha "$(jq -er '.base.sha' <<<"$PR")" \
    --arg head_ref "$(jq -er '.head.ref' <<<"$PR")" \
    --arg head_sha "$HEAD_SHA" \
    --arg current_head_sha "$CURRENT_HEAD_SHA" \
    --arg head_repo "$(jq -r '.head.repo.full_name // ""' <<<"$PR")" \
    --argjson labels "$(jq -c '[.labels[].name]' <<<"$PR")" \
    --argjson changed_files "$FILES" \
    --argjson head_parents "$PARENTS" \
    --arg parent_sha "$PARENT_SHA" \
    --argjson parent_reachable "$PARENT_REACHABLE" \
    '{
      repo: $repo,
      sender_permission: $sender_permission,
      author_login: $author_login,
      author_type: $author_type,
      author_permission: $author_permission,
      state: $state,
      draft: $draft,
      title: $title,
      base_ref: $base_ref,
      base_sha: $base_sha,
      head_ref: $head_ref,
      head_sha: $head_sha,
      current_head_sha: $current_head_sha,
      head_repo: $head_repo,
      labels: $labels,
      changed_files: $changed_files,
      head_parents: $head_parents,
      parent_sha: $parent_sha,
      parent_reachable: $parent_reachable
    }' > "$DATA"
else
  if [ -z "$BASE" ] || [ -z "$HEAD" ] || [ -z "$SOURCE_SHA" ] ||
     [ -z "$EXPECTED_HEAD_SHA" ]; then
    die "--branch requires --base, --head, --source-sha, and --expected-head-sha"
  fi

  BASE_SHA=$(gh api "repos/$REPO/git/ref/heads/$BASE" --jq '.object.sha')
  HEAD_SHA=$(gh api "repos/$REPO/git/ref/heads/$HEAD" --jq '.object.sha')
  PARENTS=$(gh api "repos/$REPO/commits/$HEAD_SHA" --jq '[.parents[].sha]')
  PARENT_REACHABLE=false
  if is_reachable "$SOURCE_SHA" "$BASE_SHA"; then
    PARENT_REACHABLE=true
  fi
  content "$SOURCE_SHA" > "$PARENT_BUILD"
  content "$HEAD_SHA" > "$HEAD_BUILD"

  jq -n \
    --arg repo "$REPO" \
    --arg base_ref "$BASE" \
    --arg base_sha "$BASE_SHA" \
    --arg head_ref "$HEAD" \
    --arg head_sha "$HEAD_SHA" \
    --arg current_head_sha "$HEAD_SHA" \
    --arg expected_head_sha "$EXPECTED_HEAD_SHA" \
    --arg head_repo "$REPO" \
    --argjson head_parents "$PARENTS" \
    --arg parent_sha "$SOURCE_SHA" \
    --argjson parent_reachable "$PARENT_REACHABLE" \
    '{
      repo: $repo,
      base_ref: $base_ref,
      base_sha: $base_sha,
      head_ref: $head_ref,
      head_sha: $head_sha,
      current_head_sha: $current_head_sha,
      expected_head_sha: $expected_head_sha,
      head_repo: $head_repo,
      changed_files: [{filename: "build.gradle.kts", status: "modified"}],
      head_parents: $head_parents,
      parent_sha: $parent_sha,
      parent_reachable: $parent_reachable
    }' > "$DATA"
fi

json_string() {
  jq -er "$1" "$DATA"
}

if [ -n "$EXPECTED_HEAD_SHA" ]; then
  [ "$(json_string '.head_sha')" = "$EXPECTED_HEAD_SHA" ] ||
    die "head SHA differs from the expected release commit"
fi
if [ -n "$SOURCE_SHA" ] && [ "$MODE" = "pr" ]; then
  [ "$(json_string '.parent_sha')" = "$SOURCE_SHA" ] ||
    die "bump parent differs from the expected release source"
fi

BASE_REF=$(json_string '.base_ref')
if [ "$BASE_REF" = "main" ]; then
  INCREMENT="minor"
elif [[ "$BASE_REF" =~ ^release/[0-9]+\.[0-9]+\._$ ]]; then
  INCREMENT="patch"
else
  die "base branch must be main or release/X.Y._"
fi

HEAD_REF=$(json_string '.head_ref')
[[ "$HEAD_REF" =~ ^automated/bump-([0-9]+)-([0-9]+)-([0-9]+)$ ]] ||
  die "head branch must match automated/bump-X-Y-Z"
BRANCH_MAJOR=${BASH_REMATCH[1]}
BRANCH_MINOR=${BASH_REMATCH[2]}
BRANCH_PATCH=${BASH_REMATCH[3]}

[ "$(json_string '.head_repo')" = "$(json_string '.repo')" ] ||
  die "head branch must belong to the base repository"
[ "$(json_string '.head_sha')" = "$(json_string '.current_head_sha')" ] ||
  die "head SHA changed during validation"
if jq -e 'has("expected_head_sha")' "$DATA" >/dev/null; then
  [ "$(json_string '.head_sha')" = "$(json_string '.expected_head_sha')" ] ||
    die "head SHA differs from the release workflow output"
fi
[ "$(jq -r '.head_parents | length' "$DATA")" -eq 1 ] ||
  die "bump commit must have exactly one parent"
[ "$(jq -r '.head_parents[0]' "$DATA")" = "$(json_string '.parent_sha')" ] ||
  die "bump commit parent differs from the recorded release source"
jq -e '.parent_reachable == true' "$DATA" >/dev/null ||
  die "release source is not reachable from the current base branch"
jq -e '.changed_files == [{filename: "build.gradle.kts", status: "modified"}]' \
  "$DATA" >/dev/null || die "PR must modify only build.gradle.kts"

VERSION_PATTERN='^version = "[0-9]+\.[0-9]+\.[0-9]+-SNAPSHOT"$'
[ "$(grep -Ec "$VERSION_PATTERN" "$PARENT_BUILD" || true)" -eq 1 ] ||
  die "parent build.gradle.kts must contain exactly one canonical root version line"
[ "$(grep -Ec "$VERSION_PATTERN" "$HEAD_BUILD" || true)" -eq 1 ] ||
  die "head build.gradle.kts must contain exactly one canonical root version line"

PARENT_LINE=$(grep -En "$VERSION_PATTERN" "$PARENT_BUILD")
HEAD_LINE=$(grep -En "$VERSION_PATTERN" "$HEAD_BUILD")
[ "${PARENT_LINE%%:*}" = "${HEAD_LINE%%:*}" ] || die "root version line moved"
PARENT_VERSION=$(sed -E 's/^[0-9]+:version = "([0-9]+\.[0-9]+\.[0-9]+)-SNAPSHOT"$/\1/' \
  <<<"$PARENT_LINE")
HEAD_VERSION=$(sed -E 's/^[0-9]+:version = "([0-9]+\.[0-9]+\.[0-9]+)-SNAPSHOT"$/\1/' \
  <<<"$HEAD_LINE")

sed -E "s/^version = \"[0-9]+\\.[0-9]+\\.[0-9]+-SNAPSHOT\"$/version = \"$PARENT_VERSION-SNAPSHOT\"/" \
  "$HEAD_BUILD" > "$TEMP_DIR/normalized-head.gradle.kts"
cmp -s "$PARENT_BUILD" "$TEMP_DIR/normalized-head.gradle.kts" ||
  die "build.gradle.kts contains changes other than the root version"

IFS=. read -r PARENT_MAJOR PARENT_MINOR PARENT_PATCH <<<"$PARENT_VERSION"
if [ "$INCREMENT" = "minor" ]; then
  if [ "$PARENT_MINOR" -ge 99 ]; then
    EXPECTED_MAJOR=$((10#$PARENT_MAJOR + 1))
    EXPECTED_MINOR=0
  else
    EXPECTED_MAJOR=$((10#$PARENT_MAJOR))
    EXPECTED_MINOR=$((10#$PARENT_MINOR + 1))
  fi
  EXPECTED_PATCH=0
else
  SERIES=${BASE_REF#release/}
  SERIES=${SERIES%._}
  [ "$PARENT_MAJOR.$PARENT_MINOR" = "$SERIES" ] ||
    die "release branch series does not match the parent version"
  if [ "$PARENT_PATCH" -ge 99 ]; then
    if [ "$PARENT_MINOR" -ge 99 ]; then
      EXPECTED_MAJOR=$((10#$PARENT_MAJOR + 1))
      EXPECTED_MINOR=0
    else
      EXPECTED_MAJOR=$((10#$PARENT_MAJOR))
      EXPECTED_MINOR=$((10#$PARENT_MINOR + 1))
    fi
    EXPECTED_PATCH=0
  else
    EXPECTED_MAJOR=$((10#$PARENT_MAJOR))
    EXPECTED_MINOR=$((10#$PARENT_MINOR))
    EXPECTED_PATCH=$((10#$PARENT_PATCH + 1))
  fi
fi
EXPECTED_VERSION="$EXPECTED_MAJOR.$EXPECTED_MINOR.$EXPECTED_PATCH"
[ "$HEAD_VERSION" = "$EXPECTED_VERSION" ] ||
  die "expected $INCREMENT bump $PARENT_VERSION -> $EXPECTED_VERSION, found $HEAD_VERSION"
[ "$BRANCH_MAJOR.$BRANCH_MINOR.$BRANCH_PATCH" = "$HEAD_VERSION" ] ||
  die "head branch version does not match build.gradle.kts"

if [ "$MODE" = "pr" ]; then
  if [ "$(json_string '.state')" != "open" ] ||
     ! jq -e '.draft == false' "$DATA" >/dev/null; then
    die "PR must be open and ready for review"
  fi
  case "$(json_string '.sender_permission')" in
    write|maintain|admin) ;;
    *) die "labeling actor must have write, maintain, or admin permission" ;;
  esac
  AUTHOR_TYPE=$(json_string '.author_type')
  AUTHOR_LOGIN=$(json_string '.author_login')
  if [ "$AUTHOR_TYPE" = "User" ]; then
    :
  elif [ "$AUTHOR_TYPE" = "Bot" ] && [ "$AUTHOR_LOGIN" = "dd-octo-sts[bot]" ]; then
    :
  else
    die "PR author must be a trusted release user or dd-octo-sts[bot]"
  fi
  case "$(json_string '.author_permission')" in
    write|maintain|admin) ;;
    *) die "PR author must have write, maintain, or admin permission" ;;
  esac
  jq -e --arg expected_label "$LABEL" \
    '.labels | index($expected_label) != null' "$DATA" >/dev/null ||
    die "PR must have the $LABEL label"
  EXPECTED_TITLE="[Automated] Bump dev version to $HEAD_VERSION"
  [ "$(json_string '.title')" = "$EXPECTED_TITLE" ] ||
    die "PR title must be exactly: $EXPECTED_TITLE"
fi

echo "Validated release bump $PARENT_VERSION -> $HEAD_VERSION at $(json_string '.head_sha')"
