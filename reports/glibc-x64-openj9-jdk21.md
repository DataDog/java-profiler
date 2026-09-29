---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 02:36:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 41-61 cores)</summary>

```
1790663461 41
1790663466 41
1790663471 41
1790663476 41
1790663481 41
1790663486 41
1790663491 41
1790663496 61
1790663501 61
1790663506 61
1790663511 61
1790663516 61
1790663521 61
1790663526 61
1790663531 61
1790663536 61
1790663541 61
1790663546 61
1790663551 61
1790663556 61
```
</details>

---

