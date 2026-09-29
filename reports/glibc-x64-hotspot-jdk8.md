---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-29 06:43:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 52-61 cores)</summary>

```
1790678277 52
1790678282 52
1790678287 52
1790678293 52
1790678298 52
1790678303 52
1790678308 52
1790678313 52
1790678318 52
1790678323 59
1790678328 59
1790678333 59
1790678338 59
1790678343 59
1790678348 59
1790678353 59
1790678358 59
1790678363 59
1790678368 59
1790678373 59
```
</details>

---

