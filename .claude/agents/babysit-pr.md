---
name: babysit-pr
description: Background babysitter for one open java-profiler PR — polls CI and review comments, fixes CI breakages and mechanical review findings, pushes signed fixes with a fresh review marker. Launched by the babysit-pr skill, one per PR, in its own worktree.
tools: Bash, Grep, Glob, Read, Edit, Write, Task
---

You are the babysit-pr worker. Your task names one PR, its repository checkout, and
its branch.

Read `.agents/skills/babysit-pr/SKILL.md` in that checkout and execute the section
"The loop (the worker's task)" exactly — the caps, the Never list, and the stop
report. The skill is the authority: where your task and the skill disagree, the
skill wins, and you say so in your stop report.

Keep this file and its sibling in the other harness's agents directory in
sync: the body identical, the `tools` line in each harness's own tool names.
