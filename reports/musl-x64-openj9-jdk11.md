---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 12:01:37 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 936 |
| Sample Rate | 15.60/sec |
| Health Score | 975% |
| Threads | 12 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1791301967 92
1791301972 92
1791301977 92
1791301982 94
1791301987 94
1791301992 94
1791301997 94
1791302002 94
1791302007 94
1791302012 94
1791302017 94
1791302022 94
1791302027 94
1791302032 94
1791302037 94
1791302042 94
1791302047 94
1791302052 94
1791302057 94
1791302062 94
```
</details>

---

