---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 11:34:38 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (4 unique values: 76-82 cores)</summary>

```
1790177319 80
1790177324 80
1790177329 80
1790177334 80
1790177339 80
1790177344 80
1790177349 80
1790177354 80
1790177359 80
1790177364 80
1790177369 80
1790177374 80
1790177379 80
1790177384 78
1790177389 78
1790177394 78
1790177399 78
1790177404 78
1790177409 76
1790177414 76
```
</details>

---

