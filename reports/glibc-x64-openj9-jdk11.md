---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-06 10:50:46 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 32-68 cores)</summary>

```
1770392730 34
1770392736 34
1770392741 34
1770392746 32
1770392751 32
1770392756 32
1770392761 32
1770392766 32
1770392771 32
1770392776 36
1770392781 36
1770392786 36
1770392791 36
1770392796 36
1770392801 36
1770392806 36
1770392811 36
1770392816 36
1770392821 68
1770392826 68
```
</details>

---

