---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:25:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 11 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (3 unique values: 73-96 cores)</summary>

```
1790173210 73
1790173215 73
1790173220 73
1790173225 73
1790173230 73
1790173235 73
1790173240 96
1790173245 96
1790173250 96
1790173255 96
1790173260 96
1790173265 96
1790173270 96
1790173275 96
1790173280 96
1790173285 96
1790173290 96
1790173295 96
1790173300 96
1790173305 96
```
</details>

---

