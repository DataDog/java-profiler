#!/usr/bin/env bash

set -euo pipefail

REPO="DataDog/java-profiler"
ACTOR=""
ACTOR_TYPE=""
FIXTURE=""

die() {
  echo "trivial approval validation failed: $*" >&2
  exit 1
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --repo) REPO=${2:-}; shift 2 ;;
    --actor) ACTOR=${2:-}; shift 2 ;;
    --actor-type) ACTOR_TYPE=${2:-}; shift 2 ;;
    --fixture) FIXTURE=${2:-}; shift 2 ;;
    *) die "unknown argument: $1" ;;
  esac
done

[ -n "$ACTOR" ] || die "label actor is required"
[ -n "$ACTOR_TYPE" ] || die "label actor type is required"

if [ -n "$FIXTURE" ]; then
  command -v jq >/dev/null || die "jq is required"
  [ -f "$FIXTURE" ] || die "fixture does not exist: $FIXTURE"
  FIXTURE_ACTOR=$(jq -er '.actor' "$FIXTURE")
  FIXTURE_ACTOR_TYPE=$(jq -er '.actor_type' "$FIXTURE")
  FIXTURE_PERMISSION=$(jq -er '.permission' "$FIXTURE")
  [ "$ACTOR" = "$FIXTURE_ACTOR" ] || die "fixture actor does not match label actor"
  [ "$ACTOR_TYPE" = "$FIXTURE_ACTOR_TYPE" ] ||
    die "fixture actor type does not match label actor type"
  PERMISSION=$FIXTURE_PERMISSION
else
  command -v gh >/dev/null || die "GitHub CLI (gh) is required"
  PERMISSION=$(gh api "repos/$REPO/collaborators/$ACTOR/permission" --jq '.permission')
fi

case "$ACTOR" in
  dependabot\[bot\]|dd-octo-sts\[bot\])
    [ "$ACTOR_TYPE" = "Bot" ] || die "trusted bot has an unexpected actor type"
    echo "Authorized trusted bot labeler: $ACTOR"
    exit 0
    ;;
esac

[ "$ACTOR_TYPE" = "User" ] || die "label actor is not a trusted human or bot"

case "$PERMISSION" in
  write|maintain|admin)
    echo "Authorized human labeler: $ACTOR ($PERMISSION)"
    ;;
  *)
    die "label actor $ACTOR has insufficient permission: $PERMISSION"
    ;;
esac
