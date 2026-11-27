---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-27 06:17:41 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (5 unique values: 58-90 cores)</summary>

```
1795777993 61
1795777998 61
1795778003 61
1795778008 61
1795778013 61
1795778018 61
1795778023 61
1795778028 61
1795778033 61
1795778038 61
1795778043 61
1795778048 61
1795778053 58
1795778058 58
1795778063 90
1795778068 90
1795778073 62
1795778078 62
1795778083 62
1795778088 62
```
</details>

---

