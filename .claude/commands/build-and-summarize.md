# build-and-summarize

<!-- Copyright 2026, Datadog, Inc -->

Execute the bash script `.claude/commands/build-and-summarize` with all provided arguments.

This script will:
- Run `./gradlew` with the specified arguments (defaults to 'build' if none provided)
- Capture full output to a timestamped log in `build/logs/`
- Show minimal live progress in the console
- Write deterministic local summaries to `build/reports/claude/gradle-summary.md` and
  `build/reports/claude/gradle-summary.json`, including on Gradle failure
- Return the actual Gradle exit status and terminate its owned process group on interruption

No external coding runner or agent is invoked. Python 3 is required; `stdbuf` is not.
Absent test counts/timings stay unknown. Inspect retained XML/JFR separately for actual
nonzero case counts, failures and skips; a successful build alone does not establish coverage.

The wrapper's inert tests run with `python3 -m unittest utils/test_gradle_summary.py`.

Pass through all arguments exactly as provided by the user.
