---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 07:43:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 7 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (4 unique values: 45-48 cores)</summary>

```
1792496331 48
1792496336 48
1792496341 48
1792496346 48
1792496351 48
1792496356 48
1792496361 48
1792496366 48
1792496371 48
1792496376 46
1792496381 46
1792496386 46
1792496391 46
1792496396 46
1792496401 46
1792496406 46
1792496411 46
1792496416 46
1792496421 46
1792496426 46
```
</details>

---

