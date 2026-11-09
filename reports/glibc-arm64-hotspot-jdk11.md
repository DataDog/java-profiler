---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 18:56:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 15 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1794268271 46
1794268276 41
1794268281 41
1794268286 41
1794268291 41
1794268296 41
1794268301 41
1794268306 41
1794268311 41
1794268316 46
1794268321 46
1794268326 46
1794268331 46
1794268336 46
1794268341 46
1794268346 46
1794268351 46
1794268356 46
1794268361 46
1794268366 46
```
</details>

---

