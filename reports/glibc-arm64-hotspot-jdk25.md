---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ❌ FAIL

**Date:** 2026-01-29 08:17:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 19 |
| Sample Rate | 0.63/sec |
| Health Score | 39% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769692277 24
1769692282 24
1769692287 24
1769692292 24
1769692297 24
1769692302 24
1769692307 24
1769692312 24
1769692317 24
1769692322 24
1769692327 24
1769692332 24
1769692337 24
1769692342 24
1769692347 24
1769692352 24
1769692357 24
1769692362 24
1769692367 24
1769692372 24
```
</details>

---

