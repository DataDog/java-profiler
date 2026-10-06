---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-06 05:52:38 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (5 unique values: 81-94 cores)</summary>

```
1791280048 81
1791280053 81
1791280058 81
1791280063 81
1791280068 87
1791280073 87
1791280078 87
1791280083 87
1791280088 87
1791280093 87
1791280098 90
1791280103 90
1791280108 90
1791280113 90
1791280118 90
1791280123 90
1791280128 92
1791280133 92
1791280138 92
1791280143 92
```
</details>

---

