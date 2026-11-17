---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 10:37:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 8 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 48-64 cores)</summary>

```
1794929317 49
1794929322 49
1794929327 49
1794929332 49
1794929337 49
1794929342 49
1794929347 49
1794929352 49
1794929357 49
1794929362 49
1794929367 51
1794929372 51
1794929377 51
1794929382 64
1794929387 64
1794929392 64
1794929397 64
1794929402 51
1794929407 51
1794929413 48
```
</details>

---

