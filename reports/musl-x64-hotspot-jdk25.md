---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-05 16:36:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1791232274 63
1791232279 63
1791232284 63
1791232289 63
1791232294 63
1791232299 63
1791232304 63
1791232309 63
1791232314 63
1791232319 63
1791232324 63
1791232329 63
1791232334 63
1791232339 63
1791232344 63
1791232349 63
1791232354 65
1791232359 65
1791232364 65
1791232369 65
```
</details>

---

