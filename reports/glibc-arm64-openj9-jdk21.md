---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-07 07:23:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (3 unique values: 24-44 cores)</summary>

```
1791371900 32
1791371905 44
1791371910 44
1791371915 44
1791371920 44
1791371925 44
1791371930 44
1791371935 44
1791371940 44
1791371945 44
1791371950 44
1791371955 44
1791371960 44
1791371965 44
1791371970 44
1791371975 44
1791371980 44
1791371985 44
1791371990 44
1791371995 44
```
</details>

---

