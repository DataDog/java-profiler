---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 08:32:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 344 |
| Sample Rate | 5.73/sec |
| Health Score | 358% |
| Threads | 9 |
| Allocations | 181 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 15 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1791980565 28
1791980570 28
1791980575 28
1791980580 28
1791980585 28
1791980590 28
1791980595 28
1791980600 28
1791980605 28
1791980610 28
1791980615 28
1791980620 28
1791980625 23
1791980630 23
1791980635 23
1791980640 23
1791980645 23
1791980650 23
1791980655 23
1791980660 23
```
</details>

---

