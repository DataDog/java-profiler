---
id: find-stack-layering-fixes
title: Fixes for #797 defects landed only in stacked #798 (cgroup lock, leaf-path cache, deferred chain invalidation)
kind: finding
tags: [pr-797, stack-layering, pr-798]
applies_to: []
source: feedback-1/find-stack-layering-fixes
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Fixes for #797 defects landed only in stacked #798 (cgroup lock, leaf-path cache, deferred chain invalidation)

## Reasoning chain
rc-4 is not a descendant of 9521394e8 (merge-base 39a8c3c76). Reviewers of #797 will keep re-finding these until ported down.

## Evidence
- Full write-up: reports/PR797Review5357763282.md; raw notes evidence/C.md. Lines at 9521394e8.
