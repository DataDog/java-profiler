---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 12:51:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 7 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (4 unique values: 33-38 cores)</summary>

```
1791391590 35
1791391595 35
1791391600 35
1791391605 35
1791391610 35
1791391615 35
1791391620 35
1791391625 35
1791391630 35
1791391635 33
1791391640 33
1791391645 38
1791391650 38
1791391655 38
1791391660 38
1791391665 38
1791391670 38
1791391675 38
1791391680 38
1791391685 38
```
</details>

---

