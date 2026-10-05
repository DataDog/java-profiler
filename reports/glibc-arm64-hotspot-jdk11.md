---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 16:36:20 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 7 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 11 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791232269 43
1791232274 43
1791232279 43
1791232284 43
1791232289 43
1791232294 48
1791232299 48
1791232304 48
1791232309 48
1791232314 48
1791232319 48
1791232324 48
1791232329 48
1791232334 48
1791232339 48
1791232344 48
1791232349 48
1791232354 48
1791232359 48
1791232364 48
```
</details>

---

