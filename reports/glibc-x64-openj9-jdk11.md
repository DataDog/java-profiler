---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 13:50:10 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 952 |
| Sample Rate | 15.87/sec |
| Health Score | 992% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 51-57 cores)</summary>

```
1793731458 51
1793731463 51
1793731468 51
1793731473 51
1793731478 51
1793731483 51
1793731488 51
1793731493 51
1793731498 51
1793731503 51
1793731508 51
1793731513 51
1793731518 51
1793731523 51
1793731528 57
1793731533 57
1793731538 54
1793731543 54
1793731548 54
1793731553 54
```
</details>

---

