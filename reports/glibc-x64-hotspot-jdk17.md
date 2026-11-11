---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 15:22:22 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 61-81 cores)</summary>

```
1794428204 66
1794428209 66
1794428214 66
1794428219 66
1794428224 66
1794428229 66
1794428234 66
1794428239 66
1794428245 66
1794428250 66
1794428255 66
1794428260 61
1794428265 61
1794428270 61
1794428275 61
1794428280 81
1794428285 81
1794428290 81
1794428295 81
1794428300 81
```
</details>

---

