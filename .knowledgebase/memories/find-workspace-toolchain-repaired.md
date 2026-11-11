---
id: find-workspace-toolchain-repaired
title: Fresh-workspace Clang can select a GCC install whose C++ headers are outside its search path - install the matching libstdc++ headers
kind: finding
tags: [workspace, clang, gcc, build, environment]
applies_to: []
source: refchain-fragmentation/find-workspace-toolchain-repaired
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


Symptom on a fresh Linux workspace: plain Clang's verbose preprocessing selects /usr/lib/gcc/x86_64-linux-gnu/14, but only /usr/include/c++/13 headers are installed and 13 is absent from the printed default search list - a translation unit including <cstring> fails with plain clang++ while g++-13 passes. Diagnosis: clang++ -x c++ -fsyntax-only --gcc-install-dir=/usr/lib/gcc/x86_64-linux-gnu/13 passes, isolating header discovery from the project.

Fix: install the libstdc++-14-dev package matching the selected GCC install (libgcc/gcc-base are usually already present); plain clang++ then builds without overrides. Pin compiler/header versions in measurement provenance.
