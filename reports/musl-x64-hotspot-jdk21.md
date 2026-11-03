---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 21:59:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1793674418 49
1793674423 49
1793674428 49
1793674433 51
1793674438 51
1793674443 51
1793674448 51
1793674453 51
1793674458 51
1793674463 51
1793674468 51
1793674473 51
1793674478 51
1793674483 51
1793674488 51
1793674493 51
1793674498 51
1793674503 51
1793674508 51
1793674513 51
```
</details>

---

