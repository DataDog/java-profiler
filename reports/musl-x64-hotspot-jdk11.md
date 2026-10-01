---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 08:26:31 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 570 |

<details>
<summary>CPU Timeline (4 unique values: 56-63 cores)</summary>

```
1790857316 63
1790857321 63
1790857327 63
1790857332 63
1790857337 61
1790857342 61
1790857347 61
1790857352 61
1790857357 61
1790857362 56
1790857367 56
1790857372 56
1790857377 56
1790857382 56
1790857387 56
1790857392 56
1790857397 56
1790857402 56
1790857407 59
1790857412 59
```
</details>

---

