---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 12:55:01 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (4 unique values: 35-53 cores)</summary>

```
1793728278 35
1793728283 35
1793728288 35
1793728293 35
1793728298 40
1793728303 40
1793728308 40
1793728313 40
1793728318 40
1793728323 40
1793728328 40
1793728333 40
1793728338 40
1793728343 40
1793728348 40
1793728353 40
1793728358 40
1793728363 53
1793728368 53
1793728373 53
```
</details>

---

