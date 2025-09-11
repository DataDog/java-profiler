---
description: Run a Gradle task, capture console to a timestamped log, then delegate parsing to the sub-agent and reply briefly.
usage: "/build-and-summarize <gradle-args...>"
---

**Task:** Build with Gradle (plain console, info level), capture output to `build/logs/`, then have `gradle-log-analyst` parse the log and write:
- `build/reports/claude/gradle-summary.md`
- `build/reports/claude/gradle-summary.json`

Make sure to use the JAVA_HOME environment variable is set appropriately. 

```bash
set -euo pipefail
mkdir -p build/logs build/reports/claude
STAMP="$(date +%Y%m%d-%H%M%S)"

# Default to 'build' if no args were given
ARGS=("$@")
if [ "${#ARGS[@]}" -eq 0 ]; then
  ARGS=(build)
fi

# Make a filename-friendly label (first arg only)
LABEL="$(echo "${ARGS[0]}" | tr '/:' '__')"
LOG="build/logs/${STAMP}-${LABEL}.log"

echo "Running: ./gradlew ${ARGS[*]} -i --console=plain"
# Capture both stdout and stderr to the log while streaming to terminal
(./gradlew "${ARGS[@]}" -i --console=plain 2>&1 | tee "$LOG") || true

# Delegate parsing to the sub-agent
echo "Delegating to gradle-logs-analyst agent..."
claude "Act as the gradle-logs-analyst agent to parse the build log at: $LOG. Generate the required gradle summary artifacts as specified in the gradle-logs-analyst agent definition."