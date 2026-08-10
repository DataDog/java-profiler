---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 11:38:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 58-92 cores)</summary>

```
1786376030 92
1786376035 92
1786376040 58
1786376045 58
1786376050 58
1786376055 58
1786376060 58
1786376065 58
1786376070 58
1786376075 58
1786376080 58
1786376085 58
1786376090 60
1786376095 60
1786376100 60
1786376105 60
1786376110 60
1786376115 60
1786376120 60
1786376125 60
```
</details>

---

