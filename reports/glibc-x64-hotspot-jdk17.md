---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-05 11:49:02 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791215036 30
1791215041 30
1791215046 30
1791215051 30
1791215056 30
1791215061 30
1791215066 30
1791215071 30
1791215076 30
1791215081 30
1791215086 30
1791215091 30
1791215096 30
1791215101 32
1791215106 32
1791215111 32
1791215116 32
1791215121 32
1791215126 32
1791215131 32
```
</details>

---

