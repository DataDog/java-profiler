---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-11 01:02:44 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 56-66 cores)</summary>

```
1791694711 56
1791694716 56
1791694721 56
1791694726 56
1791694731 58
1791694736 58
1791694741 56
1791694746 56
1791694751 56
1791694756 56
1791694761 56
1791694766 56
1791694771 56
1791694776 56
1791694781 58
1791694786 58
1791694791 58
1791694796 58
1791694801 58
1791694806 58
```
</details>

---

