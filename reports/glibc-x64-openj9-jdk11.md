---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 09:09:19 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 41-59 cores)</summary>

```
1794319451 42
1794319456 42
1794319461 42
1794319466 42
1794319471 42
1794319476 42
1794319481 42
1794319486 42
1794319491 42
1794319496 42
1794319501 42
1794319506 42
1794319511 42
1794319516 59
1794319521 59
1794319526 59
1794319531 41
1794319536 41
1794319541 41
1794319546 41
```
</details>

---

