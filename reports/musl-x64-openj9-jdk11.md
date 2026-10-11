---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-11 01:02:46 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 16-26 cores)</summary>

```
1791694711 26
1791694716 26
1791694721 26
1791694726 26
1791694731 26
1791694736 26
1791694741 26
1791694746 26
1791694751 26
1791694756 26
1791694761 26
1791694766 26
1791694771 26
1791694776 26
1791694781 26
1791694786 26
1791694791 26
1791694796 26
1791694801 26
1791694806 16
```
</details>

---

