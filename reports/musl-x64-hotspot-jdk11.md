---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:05:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 811 |
| Sample Rate | 13.52/sec |
| Health Score | 845% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (5 unique values: 64-94 cores)</summary>

```
1794391198 94
1794391203 92
1794391208 92
1794391213 92
1794391218 92
1794391223 74
1794391228 74
1794391233 64
1794391238 64
1794391243 64
1794391248 64
1794391253 64
1794391258 64
1794391263 64
1794391268 64
1794391273 68
1794391278 68
1794391283 68
1794391288 68
1794391293 68
```
</details>

---

