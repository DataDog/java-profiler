---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 08:37:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1795786351 66
1795786356 66
1795786361 64
1795786366 64
1795786371 64
1795786376 64
1795786381 64
1795786386 64
1795786391 64
1795786396 64
1795786401 64
1795786406 64
1795786411 64
1795786416 64
1795786421 64
1795786426 64
1795786431 64
1795786436 64
1795786441 64
1795786446 64
```
</details>

---

