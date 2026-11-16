---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 00:05:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 13 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794805303 40
1794805308 40
1794805313 40
1794805318 40
1794805323 40
1794805328 40
1794805333 40
1794805338 40
1794805343 40
1794805348 40
1794805353 40
1794805358 40
1794805363 40
1794805368 40
1794805373 40
1794805378 40
1794805383 40
1794805388 40
1794805393 40
1794805398 40
```
</details>

---

