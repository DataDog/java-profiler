---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 09:14:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 12 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1786367354 59
1786367359 59
1786367364 64
1786367369 64
1786367374 64
1786367379 64
1786367384 64
1786367389 64
1786367394 64
1786367399 64
1786367404 64
1786367409 64
1786367414 64
1786367419 64
1786367424 64
1786367429 64
1786367434 64
1786367439 64
1786367444 64
1786367449 64
```
</details>

---

