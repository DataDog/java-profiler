---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 03:38:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 29-39 cores)</summary>

```
1777275264 29
1777275269 34
1777275274 34
1777275279 34
1777275284 34
1777275289 34
1777275294 34
1777275299 34
1777275304 34
1777275309 34
1777275314 34
1777275319 34
1777275324 34
1777275329 34
1777275334 34
1777275339 34
1777275344 34
1777275349 34
1777275354 34
1777275359 34
```
</details>

---

