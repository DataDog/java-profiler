---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-25 08:39:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 17 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1787661351 50
1787661356 50
1787661361 50
1787661366 50
1787661371 50
1787661376 50
1787661381 50
1787661386 50
1787661391 50
1787661396 50
1787661402 50
1787661407 50
1787661412 50
1787661417 52
1787661422 52
1787661427 52
1787661432 52
1787661437 52
1787661442 52
1787661447 52
```
</details>

---

