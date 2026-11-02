---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 17:11:45 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 64-86 cores)</summary>

```
1793656917 64
1793656922 64
1793656927 64
1793656932 64
1793656937 64
1793656942 64
1793656947 64
1793656952 64
1793656957 64
1793656962 64
1793656967 64
1793656972 66
1793656977 66
1793656982 66
1793656987 66
1793656992 66
1793656997 66
1793657002 64
1793657007 64
1793657012 84
```
</details>

---

