---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 09:32:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 54-63 cores)</summary>

```
1793194029 57
1793194034 57
1793194039 57
1793194044 57
1793194049 57
1793194054 54
1793194059 54
1793194064 54
1793194069 54
1793194074 63
1793194079 63
1793194084 63
1793194089 63
1793194094 63
1793194099 63
1793194104 58
1793194109 58
1793194114 58
1793194119 58
1793194124 58
```
</details>

---

