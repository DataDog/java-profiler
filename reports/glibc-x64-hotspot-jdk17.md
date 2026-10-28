---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 05:04:13 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (3 unique values: 78-83 cores)</summary>

```
1793178061 80
1793178066 80
1793178071 78
1793178076 78
1793178081 78
1793178086 78
1793178091 78
1793178096 78
1793178101 83
1793178106 83
1793178111 83
1793178116 83
1793178121 83
1793178126 83
1793178131 83
1793178136 83
1793178141 83
1793178146 83
1793178151 83
1793178156 83
```
</details>

---

