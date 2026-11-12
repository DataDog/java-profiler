---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 10:32:59 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (5 unique values: 75-85 cores)</summary>

```
1794497236 80
1794497241 80
1794497246 80
1794497251 80
1794497256 80
1794497261 80
1794497266 78
1794497271 78
1794497276 80
1794497281 80
1794497286 80
1794497291 80
1794497296 80
1794497301 83
1794497306 83
1794497311 83
1794497316 83
1794497321 85
1794497326 85
1794497331 85
```
</details>

---

