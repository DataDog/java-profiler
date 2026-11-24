---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:31:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 157 |
| Sample Rate | 2.62/sec |
| Health Score | 164% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 14 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795530341 64
1795530346 64
1795530351 64
1795530356 64
1795530361 64
1795530366 64
1795530371 64
1795530376 64
1795530381 64
1795530386 64
1795530391 64
1795530396 64
1795530401 64
1795530406 64
1795530411 64
1795530416 64
1795530421 64
1795530426 64
1795530431 64
1795530436 64
```
</details>

---

