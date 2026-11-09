---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-09 18:56:10 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 35-41 cores)</summary>

```
1794268271 37
1794268276 37
1794268281 35
1794268286 35
1794268291 35
1794268296 35
1794268301 39
1794268306 39
1794268311 39
1794268316 39
1794268321 39
1794268326 39
1794268331 39
1794268336 39
1794268341 39
1794268346 39
1794268351 39
1794268356 39
1794268361 39
1794268366 39
```
</details>

---

