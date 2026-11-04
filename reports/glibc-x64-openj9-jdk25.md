---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 00:07:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (4 unique values: 23-46 cores)</summary>

```
1793768570 46
1793768575 42
1793768580 42
1793768585 42
1793768590 42
1793768595 40
1793768600 40
1793768605 40
1793768610 40
1793768615 40
1793768620 40
1793768625 40
1793768630 40
1793768635 40
1793768640 40
1793768645 40
1793768650 40
1793768655 40
1793768660 40
1793768665 40
```
</details>

---

