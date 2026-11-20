---
name: ci-script-change
description: Safety procedure for changing java-profiler CI configuration or the scripts that CI, Gradle or hooks run, and for deleting files or removing entries from default lists or configs. Use before editing .gitlab-ci.yml, anything under .gitlab/ or .github/, a script under utils/, or before deleting any tracked file or removing a default entry such as an antagonist, test tag or feature flag.
---

# CI script change

Scripts that CI, Gradle or hooks run carry fallbacks and environment-driven paths that
the local, common case never exercises. A rewrite that works locally can silently drop
one of them.

1. **Find every caller.** Grep the whole repository for the script's name, including
   `.gitlab-ci.yml`, `.gitlab/**`, `.github/**`, Gradle files (`qualityChecks` runs
   `utils/check-*.py`), `.githooks/`, `.claude/` and `.pi/`. Note how each caller invokes
   it: arguments, environment variables, the exit codes it expects.
2. **Enumerate the behavior branches.** Before rewriting or replacing the script, run
   `git log -p -- <script>` (or diff against the version being replaced). List every
   branch: fallbacks, env-var-driven paths, error exits. Preserve all of them unless the
   engineer asked to drop one; never narrow behavior silently while refactoring.
3. **Prove removals.** Before deleting any tracked file, or removing an item from a
   default list or config, grep the whole repository, including `.gitlab/**`. Cite the
   file and line that shows the item is inert or unused in that context. Never remove on
   assumption.
4. **Check the result.** Run a syntax check (`bash -n <script>`, `python3 -m py_compile`).
   Trace each caller from step 1 against the new script, not only the local case. Hermetic
   tests for these scripts live in `tests/` directories next to them; list them with
   `git ls-files '*/tests/*'`. Extend them for every branch you add or change.
