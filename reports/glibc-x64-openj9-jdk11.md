---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:20:12 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 9 |
| Allocations | 563 |

<details>
<summary>CPU Timeline (2 unique values: 46-71 cores)</summary>

```
1790853369 46
1790853374 46
1790853379 46
1790853384 46
1790853389 46
1790853394 46
1790853399 46
1790853404 71
1790853409 71
1790853414 71
1790853419 71
1790853424 71
1790853429 71
1790853434 71
1790853439 71
1790853444 71
1790853449 71
1790853454 71
1790853459 71
1790853464 71
```
</details>

---

