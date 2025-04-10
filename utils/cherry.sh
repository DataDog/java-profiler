#!/bin/bash
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ $# -ne 1 ]; then
  echo "Usage: $0 [<upstream-commit-hash> | --continue | --abort]"
  exit 1
fi

CMD=$1

if [[ "$CMD" == "--continue" ]] || [[ "$CMD" == "--abort" ]]; then
  GIT_DIR="$HERE/../.git"
  if [ -f "$GIT_DIR/CHERRY_PICK_HEAD" ] && [ -f "$GIT_DIR/CHERRY_COMMIT_EDITMSG" ]; then
    if [[ "$CMD" == "--continue" ]]; then
      git commit -F "$GIT_DIR/CHERRY_COMMIT_EDITMSG" --author "$(cat $GIT_DIR/COMMIT_AUTHOR_NAME) <$(cat $GIT_DIR/COMMIT_AUTHOR_EMAIL)>)" --date "$(cat $GIT_DIR/COMMIT_AUTHOR_DATE)"
    else
      git reset --hard HEAD
    fi
    rm -f $GIT_DIR/CHERRY_PICK_HEAD $GIT_DIR/CHERY_COMMIT_EDITMSG $GIT_DIR/COMMIT_AUTHOR_NAME $GIT_DIR/COMMIT_AUTHOR_EMAIL $GIT_DIR/COMMIT_AUTHOR_DATE
    exit 0
  else
    echo "No cherry-pick in progress."
    exit 1
  fi
fi

UPSTREAM_COMMIT=$1

PATCH_FILE=$(mktemp)
TMP_REWRITTEN=$(mktemp)

cleanup() {
  rm -f "$PATCH_FILE" "$TMP_REWRITTEN"
}
trap cleanup EXIT

# Step 1: Generate patch from upstream commit (only src/)
git diff-tree -p "$UPSTREAM_COMMIT" -- src/ > "$PATCH_FILE"

# Step 2: Rewrite and filter paths
awk '
  function is_cpp_or_header(path) {
    return path ~ /\.(cpp|cc|cxx|h|hpp)$/
  }
  function is_api_java(path) {
    return path ~ /^src\/api\/.*\.java$/
  }
  function translate_path(path) {
    if (is_cpp_or_header(path)) {
      sub(/^src\//, "ddprof-lib/src/main/cpp/", path)
      return path
    } else if (is_api_java(path)) {
      sub(/^src\/api\//, "ddprof-lib/src/main/java/", path)
      return path
    }
    return ""
  }

  BEGIN {
    skip = 0
  }

  /^diff --git a\// {
    a = substr($3, 3)
    b = substr($4, 3)
    a_new = translate_path(a)
    b_new = translate_path(b)
    if (a_new == "" || b_new == "") {
      skip = 1
      next
    }
    print "diff --git a/" a_new " b/" b_new
    skip = 0
    next
  }

  /^--- a\// {
    if (skip) next
    path = substr($0, 7)
    newpath = translate_path(path)
    if (newpath == "") { skip = 1; next }
    print "--- a/" newpath
    next
  }

  /^\+\+\+ b\// {
    if (skip) next
    path = substr($0, 7)
    newpath = translate_path(path)
    if (newpath == "") { skip = 1; next }
    print "+++ b/" newpath
    next
  }

  {
    if (!skip) print
  }
' "$PATCH_FILE" > "$TMP_REWRITTEN"

# Step 3: Apply the rewritten patch if it's not empty
if ! grep -q '^diff --git' "$TMP_REWRITTEN"; then
  echo "No applicable changes after path filtering. Skipping commit $UPSTREAM_COMMIT"
  exit 0
fi

# Step 4: Commit using original metadata
tree=$(git write-tree)
parent=$(git rev-parse HEAD)
author_name=$(git show -s --format='%an' "$UPSTREAM_COMMIT")
author_email=$(git show -s --format='%ae' "$UPSTREAM_COMMIT")
author_date=$(git show -s --format='%aI' "$UPSTREAM_COMMIT")
commit_message=$(git show -s --format='%s%n%n%b' "$UPSTREAM_COMMIT")

if ! grep -q "$UPSTREAM_COMMIT" <<< "$commit_message"; then
  commit_message="$commit_message

(cherry picked from commit $UPSTREAM_COMMIT)"
fi

if ! git apply --3way "$TMP_REWRITTEN"; then
  echo "Patch had conflicts. Please resolve manually, then run:"
  echo "./utils/cherry.sh --continue"
  echo "  or "
  echo "  git add <resolved files>"
  echo "  git commit --author=\"$author_name <$author_email>\" --date=\"$author_date\" -m \"$commit_message\""
  echo
  echo "$author_date" > .git/COMMIT_AUTHOR_DATE
  echo "$author_email" > .git/COMMIT_AUTHOR_EMAIL
  echo "$author_name" > .git/COMMIT_AUTHOR_NAME
  echo "$UPSTREAM_COMMIT" > .git/CHERRY_PICK_HEAD
  echo "$commit_message" > .git/CHERRY_COMMIT_EDITMSG
  exit 1
fi

GIT_AUTHOR_NAME="$author_name" \
GIT_AUTHOR_EMAIL="$author_email" \
GIT_AUTHOR_DATE="$author_date" \
git commit-tree "$tree" -p "$parent" -m "$commit_message" | xargs git reset --hard
