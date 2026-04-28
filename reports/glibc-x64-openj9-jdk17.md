---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-28 09:57:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (6 unique values: 70-79 cores)</summary>

```
1777384459 70
1777384464 71
1777384469 71
1777384474 71
1777384479 71
1777384484 71
1777384489 71
1777384494 71
1777384499 71
1777384504 73
1777384509 73
1777384514 73
1777384519 73
1777384524 73
1777384529 74
1777384534 74
1777384539 74
1777384544 74
1777384549 74
1777384554 74
```
</details>

---

