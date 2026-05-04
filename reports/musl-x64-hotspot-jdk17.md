---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-03 21:21:07 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 50-54 cores)</summary>

```
1777857352 50
1777857357 50
1777857362 50
1777857367 50
1777857372 54
1777857377 54
1777857382 54
1777857387 54
1777857392 54
1777857397 54
1777857402 54
1777857407 54
1777857412 54
1777857417 54
1777857422 54
1777857427 54
1777857432 54
1777857438 54
1777857443 54
1777857448 54
```
</details>

---

