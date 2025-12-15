---
description: Run and analyze JMH benchmarks via the jmh-benchmarks subagent.
argument-hint: "[filter or 'all'] [mode: quick|full] [baseline-path(optional)]"
allowed-tools: Bash(./gradlew:*), Bash(gradlew:*), Bash(./mvnw:*), Bash(mvn:*), Bash(java:*), Read, Glob, Grep, Write
---

You MUST route this request through the `jmh-benchmarks` subagent for all heavy lifting,
so that JMH logs and result files stay in its separate context and do not pollute the
main conversation.

User arguments (raw): `$ARGUMENTS`

Interpretation:
- $1  → benchmark filter or "all" (optional)
- $2  → mode: "quick" (default) or "full" (optional)
- $3  → optional baseline path to compare against

If $1 is empty:
- Treat it as "all" benchmarks in quick mode.

If $1 is provided and not "all":
- Treat it as a JMH benchmark include pattern (e.g. regex or substring)
  and pass it to JMH according to the project's conventions.

If $2 is "full":
- Ask the `jmh-benchmarks` subagent to use the project's full/fat JMH configuration.
  Otherwise:
- Use "quick" mode settings as defined in the subagent prompt.

If $3 is provided:
- Treat it as a file path to a previous JMH results file and request a comparison
  against the new run.

Your task:

1. Summarize what will be done based on the provided arguments (filter, mode, baseline).
2. Explicitly instruct the `jmh-benchmarks` subagent to:
  - Detect the build tool (Gradle vs Maven) and JMH integration.
  - Choose an appropriate JMH command and run it, respecting the filter/mode.
  - Locate JMH result files (JSON/CSV/text).
  - Analyze and summarize the results.
  - If a baseline is available (either from $3 or default baseline locations),
    perform a regression comparison.
3. Ask the subagent to keep all large logs and raw results in its own context, and
   only return a concise summary to this main thread.
4. Present the final answer as:
  - A short description of what was run (command, mode, filter).
  - A table of key benchmarks with score, error, units.
  - If baseline available: a table of regressions/improvements with percentage change.
  - Bullet points with recommendations for further investigation.

Do not run JMH directly yourself in this command body. Always delegate to the
`jmh-benchmarks` subagent and act as a thin orchestrator and summarizer.
