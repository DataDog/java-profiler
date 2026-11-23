---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:56:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 31-33 cores)</summary>

```
1795434731 31
1795434736 31
1795434741 31
1795434746 31
1795434751 31
1795434756 31
1795434761 31
1795434766 31
1795434771 31
1795434776 31
1795434781 31
1795434786 31
1795434791 31
1795434796 31
1795434801 31
1795434806 31
1795434811 31
1795434816 31
1795434821 31
1795434826 33
```
</details>

---

