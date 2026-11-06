---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-06 10:29:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793978560 43
1793978565 45
1793978570 45
1793978575 45
1793978580 45
1793978585 45
1793978590 45
1793978595 45
1793978600 45
1793978605 45
1793978610 45
1793978615 45
1793978620 45
1793978625 48
1793978630 48
1793978635 48
1793978640 48
1793978645 48
1793978650 48
1793978655 48
```
</details>

---

