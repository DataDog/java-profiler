---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 17:11:45 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 407 |
| Sample Rate | 6.78/sec |
| Health Score | 424% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 39-43 cores)</summary>

```
1793656924 39
1793656929 39
1793656934 39
1793656939 39
1793656944 41
1793656949 41
1793656954 41
1793656959 41
1793656964 41
1793656969 43
1793656974 43
1793656979 39
1793656984 39
1793656989 39
1793656994 39
1793656999 39
1793657004 39
1793657009 39
1793657014 39
1793657019 39
```
</details>

---

