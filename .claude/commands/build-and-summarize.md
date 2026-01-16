# build-and-summarize

Execute the bash script `~/.claude/commands/build-and-summarize` with all provided arguments.

This script will:
- Run `./gradlew` with the specified arguments (defaults to 'build' if none provided)
- Capture full output to a timestamped log in `build/logs/`
- Show minimal live progress in the console
- Delegate to the `gradle-logs-analyst` agent for structured analysis

Pass through all arguments exactly as provided by the user.
