---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-26 10:30:27 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
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
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787754291 64
1787754296 64
1787754301 64
1787754306 64
1787754311 64
1787754316 64
1787754321 64
1787754326 64
1787754331 64
1787754336 64
1787754341 64
1787754346 64
1787754351 64
1787754356 64
1787754361 64
1787754366 64
1787754371 64
1787754376 64
1787754381 64
1787754386 64
```
</details>

---

