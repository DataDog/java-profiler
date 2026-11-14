---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-14 05:55:36 EST

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 17-18 cores)</summary>

```
1794653418 18
1794653423 18
1794653428 18
1794653433 18
1794653438 18
1794653443 18
1794653448 17
1794653453 17
1794653458 17
1794653463 17
1794653468 17
1794653473 17
1794653478 17
1794653483 17
1794653488 17
1794653493 17
1794653498 17
1794653503 17
1794653508 17
1794653513 17
```
</details>

---

