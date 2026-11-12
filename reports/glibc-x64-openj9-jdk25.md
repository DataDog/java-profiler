---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:09:37 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 31-50 cores)</summary>

```
1794495912 33
1794495917 33
1794495922 33
1794495927 33
1794495932 33
1794495937 33
1794495942 33
1794495947 31
1794495952 31
1794495957 31
1794495962 31
1794495967 31
1794495972 31
1794495977 31
1794495982 50
1794495987 50
1794495992 50
1794495997 50
1794496002 50
1794496007 50
```
</details>

---

