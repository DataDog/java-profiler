---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 08:46:05 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (5 unique values: 57-92 cores)</summary>

```
1786538521 92
1786538526 92
1786538531 92
1786538537 59
1786538542 59
1786538547 59
1786538552 59
1786538557 57
1786538562 57
1786538567 59
1786538572 59
1786538577 59
1786538582 59
1786538587 59
1786538592 59
1786538597 61
1786538602 61
1786538607 61
1786538612 61
1786538617 61
```
</details>

---

