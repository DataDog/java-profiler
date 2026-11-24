---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:31:26 EST

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
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 13 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795530276 43
1795530281 43
1795530286 43
1795530291 43
1795530296 43
1795530301 43
1795530306 43
1795530311 43
1795530316 43
1795530321 48
1795530326 48
1795530331 48
1795530336 48
1795530341 48
1795530346 48
1795530351 48
1795530356 48
1795530361 48
1795530366 48
1795530371 48
```
</details>

---

