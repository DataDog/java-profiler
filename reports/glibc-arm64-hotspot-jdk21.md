---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 09:43:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794494256 51
1794494261 51
1794494266 51
1794494271 51
1794494276 51
1794494281 51
1794494286 46
1794494291 46
1794494296 46
1794494301 46
1794494306 46
1794494311 46
1794494316 46
1794494321 46
1794494326 46
1794494331 46
1794494336 46
1794494341 46
1794494346 46
1794494351 46
```
</details>

---

