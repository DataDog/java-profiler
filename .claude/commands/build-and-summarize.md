# build-and-summarize

Runs `./gradlew` with full output captured to a timestamped log, shows minimal live progress (task starts + final build/test summary), then asks the `gradle-logs-analyst` agent to produce structured artifacts from the log.

## Usage
```bash
./.claude/commands/build-and-summarize [<gradle-args>...]