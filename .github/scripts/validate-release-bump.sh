#!/usr/bin/env bash

set -euo pipefail

LABEL="trivial"
MODE="pr"
FIXTURE=""
REPO="DataDog/java-profiler"
PR_NUMBER=""
SENDER=""
SENDER_TYPE=""
BASE=""
HEAD=""
SOURCE_SHA=""
EXPECTED_HEAD_SHA=""
LOCAL_RELEASE_TAG=""
FIRST_PATCH=false
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
    --sender-type) SENDER_TYPE=${2:-}; shift 2 ;;
    --branch) MODE="branch"; shift ;;
    --base) BASE=${2:-}; shift 2 ;;
    --head) HEAD=${2:-}; shift 2 ;;
    --source-sha) SOURCE_SHA=${2:-}; shift 2 ;;
    --expected-head-sha) EXPECTED_HEAD_SHA=${2:-}; shift 2 ;;
    --local-release-tag) LOCAL_RELEASE_TAG=${2:-}; shift 2 ;;
    --first-patch) FIRST_PATCH=true; shift ;;
    *) die "unknown argument: $1" ;;
  esac
done

command -v jq >/dev/null || die "jq is required"
TEMP_DIR=$(mktemp -d)
DATA="$TEMP_DIR/data.json"
PARENT_BUILD="$TEMP_DIR/parent-build.gradle.kts"
HEAD_BUILD="$TEMP_DIR/head-build.gradle.kts"
RELEASE_BUILD="$TEMP_DIR/release-build.gradle.kts"
SOURCE_BUILD="$TEMP_DIR/source-build.gradle.kts"

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
  jq 'del(.parent_build, .head_build, .release_build, .source_build)' "$FIXTURE" > "$DATA"
  jq -j '.parent_build' "$FIXTURE" > "$PARENT_BUILD"
  jq -j '.head_build' "$FIXTURE" > "$HEAD_BUILD"
  jq -j '.release_build // ""' "$FIXTURE" > "$RELEASE_BUILD"
  jq -j '.source_build // ""' "$FIXTURE" > "$SOURCE_BUILD"
elif [ "$MODE" = "pr" ]; then
  if [ -z "$PR_NUMBER" ] || [ -z "$SENDER" ] || [ -z "$SENDER_TYPE" ]; then
    die "PR validation requires --pr-number, --sender, and --sender-type"
  fi
  [[ "$PR_NUMBER" =~ ^[0-9]+$ ]] || die "invalid PR number"

  PR=$(gh api "repos/$REPO/pulls/$PR_NUMBER")
  AUTHOR=$(jq -er '.user.login' <<<"$PR")
  HEAD_SHA=$(jq -er '.head.sha' <<<"$PR")
  COMMIT=$(gh api "repos/$REPO/commits/$HEAD_SHA")
  PARENTS=$(jq -c '[.parents[].sha]' <<<"$COMMIT")
  PARENT_SHA=$(jq -r 'if length == 1 then .[0] else "" end' <<<"$PARENTS")
  FILES=$(gh api --paginate "repos/$REPO/pulls/$PR_NUMBER/files?per_page=100" \
    --slurp | jq -c 'add | map({filename, status})')
  CURRENT_HEAD_SHA=$(gh api "repos/$REPO/pulls/$PR_NUMBER" --jq '.head.sha')
  SENDER_PERMISSION="none"
  if [ "$SENDER" != "dd-octo-sts[bot]" ] || [ "$SENDER_TYPE" != "Bot" ]; then
    SENDER_PERMISSION=$(permission "$SENDER")
  fi
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
    --arg sender_login "$SENDER" \
    --arg sender_type "$SENDER_TYPE" \
    --arg sender_permission "$SENDER_PERMISSION" \
    --arg author_login "$AUTHOR" \
    --arg author_type "$(jq -er '.user.type' <<<"$PR")" \
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
      sender_login: $sender_login,
      sender_type: $sender_type,
      sender_permission: $sender_permission,
      author_login: $author_login,
      author_type: $author_type,
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
  COMMIT=$(gh api "repos/$REPO/commits/$HEAD_SHA")
  PARENTS=$(jq -c '[.parents[].sha]' <<<"$COMMIT")
  PARENT_SHA=$(jq -r 'if length == 1 then .[0] else "" end' <<<"$PARENTS")
  FILES=$(jq -c '[.files[] | {filename, status}]' <<<"$COMMIT")
  PARENT_REACHABLE=false
  if is_reachable "$SOURCE_SHA" "$BASE_SHA"; then
    PARENT_REACHABLE=true
  fi
  if [ -n "$PARENT_SHA" ]; then
    content "$PARENT_SHA" > "$PARENT_BUILD"
  else
    : > "$PARENT_BUILD"
  fi
  if [ "$FIRST_PATCH" = "true" ]; then
    content "$SOURCE_SHA" > "$SOURCE_BUILD"
  else
    : > "$SOURCE_BUILD"
  fi
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
    --argjson changed_files "$FILES" \
    --argjson head_parents "$PARENTS" \
    --arg parent_sha "$PARENT_SHA" \
    --arg source_sha "$SOURCE_SHA" \
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
      changed_files: $changed_files,
      head_parents: $head_parents,
      parent_sha: $parent_sha,
      source_sha: $source_sha,
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
if [ "$MODE" = "branch" ] && [ "$FIRST_PATCH" != "true" ]; then
  [ "$(json_string '.parent_sha')" = "$SOURCE_SHA" ] ||
    die "bump commit parent differs from the requested release source"
fi
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

validate_first_patch_release() {
  [ "$MODE" = "branch" ] || die "--first-patch is allowed only for branch preflight validation"
  [ -n "$LOCAL_RELEASE_TAG" ] || die "first patch validation requires --local-release-tag"
  [ "$(json_string '.source_sha')" = "$SOURCE_SHA" ] ||
    die "first patch source differs from the requested release source"

  local release_tag_sha release_tag_annotated release_parents release_changed_files
  local source_tag_annotated source_tag_reachable
  if [ -n "$FIXTURE" ]; then
    release_tag_sha=$(json_string '.release_tag_sha')
    release_tag_annotated=$(jq -er '.release_tag_annotated' "$DATA")
    release_parents=$(jq -c '.release_parents' "$DATA")
    release_changed_files=$(jq -c '.release_changed_files' "$DATA")
    source_tag_annotated=$(jq -er '.source_tag_annotated' "$DATA")
    source_tag_reachable=$(jq -er '.source_tag_reachable' "$DATA")
  else
    [ "$(git cat-file -t "refs/tags/$LOCAL_RELEASE_TAG" 2>/dev/null)" = "tag" ] ||
      die "first patch release tag $LOCAL_RELEASE_TAG must be annotated"
    release_tag_sha=$(git rev-parse "refs/tags/$LOCAL_RELEASE_TAG^{commit}")
    release_tag_annotated=true

    local release_commit source_tag
    release_commit=$(gh api "repos/$REPO/commits/$(json_string '.parent_sha')")
    release_parents=$(jq -c '[.parents[].sha]' <<<"$release_commit")
    release_changed_files=$(jq -c '[.files[] | {filename, status}]' <<<"$release_commit")

    source_tag="v_$(sed -nE \
      's/^version = "([0-9]+\.[0-9]+\.[0-9]+)-SNAPSHOT"$/\1/p' "$SOURCE_BUILD")"
    if [ "$(git cat-file -t "refs/tags/$source_tag" 2>/dev/null)" = "tag" ]; then
      source_tag_annotated=true
    else
      source_tag_annotated=false
    fi
    if [ "$source_tag_annotated" = "true" ] &&
       git merge-base --is-ancestor "refs/tags/$source_tag^{commit}" "$SOURCE_SHA"; then
      source_tag_reachable=true
    else
      source_tag_reachable=false
    fi
  fi

  [ "$LOCAL_RELEASE_TAG" = "v_$PARENT_VERSION" ] ||
    die "first patch release tag must be v_$PARENT_VERSION"
  [ "$release_tag_annotated" = "true" ] ||
    die "first patch release tag v_$PARENT_VERSION must be annotated"
  [ "$release_tag_sha" = "$(json_string '.parent_sha')" ] ||
    die "first patch release tag must identify the bump parent"
  [ "$(jq -r 'length' <<<"$release_parents")" -eq 1 ] ||
    die "first patch release commit must have exactly one parent"
  [ "$(jq -r '.[0]' <<<"$release_parents")" = "$SOURCE_SHA" ] ||
    die "first patch release commit parent differs from the requested source"
  jq -e '. == [{filename: "build.gradle.kts", status: "modified"}]' \
    <<<"$release_changed_files" >/dev/null ||
    die "first patch release commit must modify only build.gradle.kts"
  [ "$source_tag_annotated" = "true" ] ||
    die "first patch source tag must be annotated"
  [ "$source_tag_reachable" = "true" ] ||
    die "first patch source tag is not reachable from the requested source"

  [ "$(grep -Ec "$VERSION_PATTERN" "$SOURCE_BUILD" || true)" -eq 1 ] ||
    die "first patch source build.gradle.kts must contain one canonical root version line"
  local source_line source_version source_major source_minor source_patch
  source_line=$(grep -En "$VERSION_PATTERN" "$SOURCE_BUILD")
  [ "${source_line%%:*}" = "${PARENT_LINE%%:*}" ] ||
    die "first patch root version line moved"
  source_version=$(sed -E \
    's/^[0-9]+:version = "([0-9]+\.[0-9]+\.[0-9]+)-SNAPSHOT"$/\1/' \
    <<<"$source_line")
  IFS=. read -r source_major source_minor source_patch <<<"$source_version"
  [ "$source_patch" -eq 0 ] || die "first patch source version must end in .0"
  [ "$PARENT_MAJOR.$PARENT_MINOR.$PARENT_PATCH" = \
    "$source_major.$source_minor.$((source_patch + 1))" ] ||
    die "first patch release version must increment the source patch once"
  sed -E \
    "s/^version = \"[0-9]+\\.[0-9]+\\.[0-9]+-SNAPSHOT\"$/version = \"$source_version-SNAPSHOT\"/" \
    "$PARENT_BUILD" > "$TEMP_DIR/normalized-first-patch.gradle.kts"
  cmp -s "$SOURCE_BUILD" "$TEMP_DIR/normalized-first-patch.gradle.kts" ||
    die "first patch release commit contains changes other than the root version"
}

if [ "$FIRST_PATCH" = "true" ]; then
  validate_first_patch_release
elif [ -n "$LOCAL_RELEASE_TAG" ] && [ "$MODE" != "branch" ]; then
  die "--local-release-tag is allowed only for branch preflight validation"
fi

validate_major_release() {
  local release_major=$1
  local release_version="$release_major.0.0"
  local release_branch="release/$release_major.0._"
  local release_ref_sha release_tag_sha release_tag_annotated
  local release_parents release_changed_files

  if [ -n "$FIXTURE" ]; then
    release_ref_sha=$(json_string '.release_ref_sha')
    release_tag_sha=$(json_string '.release_tag_sha')
    release_tag_annotated=$(jq -er '.release_tag_annotated' "$DATA")
    release_parents=$(jq -c '.release_parents' "$DATA")
    release_changed_files=$(jq -c '.release_changed_files' "$DATA")
  else
    local tag_ref tag_object release_commit
    release_ref_sha=$(gh api "repos/$REPO/git/ref/heads/$release_branch" --jq '.object.sha')
    if [ -n "$LOCAL_RELEASE_TAG" ]; then
      [ "$MODE" = "branch" ] ||
        die "--local-release-tag is allowed only for branch preflight validation"
      [ "$LOCAL_RELEASE_TAG" = "v_$release_version" ] ||
        die "local major release tag must be v_$release_version"
      [ "$(git cat-file -t "refs/tags/$LOCAL_RELEASE_TAG" 2>/dev/null)" = "tag" ] ||
        die "local major release tag $LOCAL_RELEASE_TAG must be annotated"
      release_tag_sha=$(git rev-parse "refs/tags/$LOCAL_RELEASE_TAG^{commit}")
    else
      tag_ref=$(gh api "repos/$REPO/git/ref/tags/v_$release_version")
      [ "$(jq -er '.object.type' <<<"$tag_ref")" = "tag" ] ||
        die "major release tag v_$release_version must be annotated"
      tag_object=$(gh api "repos/$REPO/git/tags/$(jq -er '.object.sha' <<<"$tag_ref")")
      [ "$(jq -er '.object.type' <<<"$tag_object")" = "commit" ] ||
        die "major release tag v_$release_version must point to a commit"
      release_tag_sha=$(jq -er '.object.sha' <<<"$tag_object")
    fi
    release_tag_annotated=true
    release_commit=$(gh api "repos/$REPO/commits/$release_ref_sha")
    release_parents=$(jq -c '[.parents[].sha]' <<<"$release_commit")
    release_changed_files=$(jq -c '[.files[] | {filename, status}]' <<<"$release_commit")
    content "$release_ref_sha" > "$RELEASE_BUILD"
  fi

  [ "$release_tag_annotated" = "true" ] ||
    die "major release tag v_$release_version must be annotated"
  [ "$release_ref_sha" = "$release_tag_sha" ] ||
    die "major release branch and tag must identify the same commit"
  [ "$(jq -r 'length' <<<"$release_parents")" -eq 1 ] ||
    die "major release commit must have exactly one parent"
  [ "$(jq -r '.[0]' <<<"$release_parents")" = "$(json_string '.parent_sha')" ] ||
    die "major release commit parent differs from the bump source"
  jq -e '. == [{filename: "build.gradle.kts", status: "modified"}]' \
    <<<"$release_changed_files" >/dev/null ||
    die "major release commit must modify only build.gradle.kts"

  [ "$(grep -Ec "$VERSION_PATTERN" "$RELEASE_BUILD" || true)" -eq 1 ] ||
    die "major release build.gradle.kts must contain one canonical root version line"
  local release_line actual_release_version
  release_line=$(grep -En "$VERSION_PATTERN" "$RELEASE_BUILD")
  [ "${release_line%%:*}" = "${PARENT_LINE%%:*}" ] ||
    die "major release root version line moved"
  actual_release_version=$(sed -E \
    's/^[0-9]+:version = "([0-9]+\.[0-9]+\.[0-9]+)-SNAPSHOT"$/\1/' \
    <<<"$release_line")
  [ "$actual_release_version" = "$release_version" ] ||
    die "major release branch must contain $release_version-SNAPSHOT"
  sed -E \
    "s/^version = \"[0-9]+\\.[0-9]+\\.[0-9]+-SNAPSHOT\"$/version = \"$PARENT_VERSION-SNAPSHOT\"/" \
    "$RELEASE_BUILD" > "$TEMP_DIR/normalized-release.gradle.kts"
  cmp -s "$PARENT_BUILD" "$TEMP_DIR/normalized-release.gradle.kts" ||
    die "major release commit contains changes other than the root version"
}

if [ "$INCREMENT" = "minor" ]; then
  if [ "$PARENT_MINOR" -ge 99 ]; then
    EXPECTED_MAJOR=$((10#$PARENT_MAJOR + 1))
    EXPECTED_MINOR=0
  else
    EXPECTED_MAJOR=$((10#$PARENT_MAJOR))
    EXPECTED_MINOR=$((10#$PARENT_MINOR + 1))
  fi
  EXPECTED_PATCH=0
  EXPECTED_VERSION="$EXPECTED_MAJOR.$EXPECTED_MINOR.$EXPECTED_PATCH"
  if [ "$HEAD_VERSION" != "$EXPECTED_VERSION" ]; then
    MAJOR_RELEASE_MAJOR=$((10#$PARENT_MAJOR + 1))
    MAJOR_RELEASE_BUMP="$MAJOR_RELEASE_MAJOR.1.0"
    [ "$HEAD_VERSION" = "$MAJOR_RELEASE_BUMP" ] ||
      die "expected minor bump $PARENT_VERSION -> $EXPECTED_VERSION or validated major-release bump -> $MAJOR_RELEASE_BUMP, found $HEAD_VERSION"
    validate_major_release "$MAJOR_RELEASE_MAJOR"
  fi
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
  EXPECTED_VERSION="$EXPECTED_MAJOR.$EXPECTED_MINOR.$EXPECTED_PATCH"
  [ "$HEAD_VERSION" = "$EXPECTED_VERSION" ] ||
    die "expected patch bump $PARENT_VERSION -> $EXPECTED_VERSION, found $HEAD_VERSION"
fi
[ "$BRANCH_MAJOR.$BRANCH_MINOR.$BRANCH_PATCH" = "$HEAD_VERSION" ] ||
  die "head branch version does not match build.gradle.kts"

if [ "$MODE" = "pr" ]; then
  if [ "$(json_string '.state')" != "open" ] ||
     ! jq -e '.draft == false' "$DATA" >/dev/null; then
    die "PR must be open and ready for review"
  fi
  if [ "$(json_string '.sender_login')" = "dd-octo-sts[bot]" ] &&
     [ "$(json_string '.sender_type')" = "Bot" ]; then
    :
  else
    [ "$(json_string '.sender_type')" = "User" ] ||
      die "labeling actor must be the release STS bot or a trusted human"
    case "$(json_string '.sender_permission')" in
      write|maintain|admin) ;;
      *) die "human labeling actor must have write, maintain, or admin permission" ;;
    esac
  fi
  if [ "$(json_string '.author_login')" != "github-actions[bot]" ] ||
     [ "$(json_string '.author_type')" != "Bot" ]; then
    die "release bump PR must be created by github-actions[bot]"
  fi
  jq -e --arg expected_label "$LABEL" \
    '.labels | index($expected_label) != null' "$DATA" >/dev/null ||
    die "PR must have the $LABEL label"
  EXPECTED_TITLE="[Automated] Bump dev version to $HEAD_VERSION"
  [ "$(json_string '.title')" = "$EXPECTED_TITLE" ] ||
    die "PR title must be exactly: $EXPECTED_TITLE"
fi

echo "Validated release bump $PARENT_VERSION -> $HEAD_VERSION at $(json_string '.head_sha')"
