---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 05:47:56 EST

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 16-51 cores)</summary>

```
1795344236 18
1795344241 18
1795344246 18
1795344251 18
1795344256 18
1795344261 16
1795344266 16
1795344271 49
1795344276 49
1795344281 49
1795344286 51
1795344291 51
1795344296 46
1795344301 46
1795344306 46
1795344311 46
1795344316 46
1795344321 46
1795344326 46
1795344331 46
```
</details>

---

