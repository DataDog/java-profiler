---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:54:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1791470950 86
1791470955 86
1791470960 86
1791470965 86
1791470970 86
1791470975 86
1791470980 86
1791470985 86
1791470990 84
1791470995 84
1791471000 84
1791471005 84
1791471010 84
1791471015 84
1791471020 84
1791471025 84
1791471030 84
1791471035 84
1791471040 84
1791471045 84
```
</details>

---

