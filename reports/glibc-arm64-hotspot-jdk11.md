---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 06:43:03 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1790678306 40
1790678311 40
1790678316 40
1790678321 40
1790678326 40
1790678331 40
1790678336 40
1790678341 40
1790678346 40
1790678351 40
1790678356 40
1790678361 40
1790678366 40
1790678371 40
1790678376 40
1790678381 40
1790678386 40
1790678391 40
1790678396 40
1790678401 40
```
</details>

---

