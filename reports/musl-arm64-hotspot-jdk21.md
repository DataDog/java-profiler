---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-25 09:23:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 11 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 8-10 cores)</summary>

```
1790342288 8
1790342293 8
1790342298 8
1790342303 8
1790342308 8
1790342313 8
1790342318 8
1790342323 8
1790342328 8
1790342333 8
1790342338 8
1790342343 8
1790342348 8
1790342353 8
1790342358 8
1790342363 8
1790342368 8
1790342373 8
1790342378 8
1790342383 8
```
</details>

---

