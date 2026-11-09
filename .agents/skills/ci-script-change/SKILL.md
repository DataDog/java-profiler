---
name: ci-script-change
description: Safety procedure for changing java-profiler CI configuration or the scripts CI runs, and for removing an item from a default list or config. Use before editing .gitlab-ci.yml, anything under .gitlab/ or .github/workflows/, a script a CI job invokes, or before deleting a script or removing a default entry such as an antagonist, test tag or feature flag.
---

# CI script change

CI scripts carry fallbacks and environment-driven paths that the local, common case never
exercises. A rewrite that works locally can silently drop one of them.

1. **Find every caller.** Grep `.gitlab-ci.yml`, `.gitlab/**`, `.github/workflows/**` and
   `utils/` for the script. Note how each job invokes it: arguments, environment
   variables, the exit codes it expects.
2. **Enumerate the behavior branches.** Before rewriting or replacing the script, run
   `git log -p -- <script>` (or diff against the version being replaced). List every
   branch: fallbacks, env-var-driven paths, error exits. Preserve all of them unless the
   engineer asked to drop one; never narrow behavior silently while refactoring.
3. **Prove removals.** Before removing an item from a default list or config, or deleting a
   script or file, grep the whole repository, including `.gitlab/**`. Cite the file and
   line that shows the item is inert or unused in that context. Never remove on
   assumption.
4. **Check the result.** Run a syntax check (`bash -n <script>`, `python3 -m py_compile`).
   Trace each calling job from step 1 against the new script, not only the local case.
   Hermetic tests for these scripts live in `utils/tests/`, `.github/scripts/tests/` and
   `.gitlab/scripts/tests/`; extend them for every branch you add or change.
