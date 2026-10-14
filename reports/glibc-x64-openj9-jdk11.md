---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 11:49:33 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1791992617 80
1791992622 80
1791992627 82
1791992632 82
1791992637 82
1791992642 82
1791992647 82
1791992652 82
1791992657 82
1791992662 82
1791992667 82
1791992672 82
1791992677 82
1791992682 82
1791992687 82
1791992692 82
1791992697 82
1791992702 82
1791992707 82
1791992712 82
```
</details>

---

