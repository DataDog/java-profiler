---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:39:50 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 19-63 cores)</summary>

```
1795793615 19
1795793620 19
1795793625 19
1795793630 19
1795793635 35
1795793640 35
1795793645 35
1795793650 35
1795793655 35
1795793660 35
1795793665 63
1795793670 63
1795793675 46
1795793680 46
1795793685 46
1795793690 46
1795793695 46
1795793700 46
1795793705 46
1795793710 46
```
</details>

---

