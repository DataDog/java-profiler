---
description: Compare upstream vs local for a given filename and generate universal patch entries via the Patch Analyst agent.
usage: "/compare-and-patch <filename>"
---

**Task:** Resolve the upstream and local paths for the provided `<filename>`,
then delegate to the `patch-analyst` sub-agent to read `gradle/patching.gradle`,
compute the diff (ignoring newline and copyright-only changes),
and write two artifacts:
- `build/reports/claude/patches/<FILE>.patch.json`
- `build/reports/claude/patches/<FILE>.patch.md`

```bash
set -euo pipefail

if [ $# -lt 1 ]; then
  echo "Usage: /compare-and-patch <filename>"
  exit 2
fi

FILE="$1"
UP_ROOT="ddprof-lib/build/async-profiler/src"
LOCAL_ROOT="ddprof-lib/src/main/cpp"

mkdir -p build/reports/claude/patches

# Resolve canonical upstream and local paths
UP_CANON="$UP_ROOT/$FILE"
LOCAL_CANON="$LOCAL_ROOT/$FILE"

# If direct paths don't exist, try to find by basename match inside each root
if [ ! -f "$UP_CANON" ]; then
  FOUND_UP=$(find "$UP_ROOT" -type f -name "$(basename "$FILE")" -maxdepth 1 2>/dev/null | head -n1 || true)
  if [ -n "$FOUND_UP" ]; then UP_CANON="$FOUND_UP"; fi
fi

if [ ! -f "$LOCAL_CANON" ]; then
  FOUND_LOCAL=$(find "$LOCAL_ROOT" -type f -name "$(basename "$FILE")" -maxdepth 1 2>/dev/null | head -n1 || true)
  if [ -n "$FOUND_LOCAL" ]; then LOCAL_CANON="$FOUND_LOCAL"; fi
fi

# Minimal existence check—agent will handle edge cases and write a status
if [ ! -f "$UP_CANON" ]; then
  echo "Upstream file not found under $UP_ROOT for $FILE"
fi
if [ ! -f "$LOCAL_CANON" ]; then
  echo "Local file not found under $LOCAL_ROOT for $FILE"
fi

echo "Resolved:"
echo "  upstream: $UP_CANON"
echo "  local:    $LOCAL_CANON"

# NOTE: Do not compute the diff here; let the agent do normalization and policy (ignore EOL/copyright).
# Delegate to the patch-analyst agent with resolved paths

echo "Delegating to patch-analyst agent..."
claude "Act as the patch-analyst agent to analyze $FILE. Use upstream file: $UP_CANON and local file: $LOCAL_CANON. Generate the required patch analysis artifacts as specified in the patch-analyst agent definition."