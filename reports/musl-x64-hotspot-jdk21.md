---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-07 07:56:32 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 71-96 cores)</summary>

```
1786103461 71
1786103466 71
1786103471 71
1786103476 71
1786103481 71
1786103486 71
1786103491 96
1786103496 96
1786103501 96
1786103506 96
1786103511 94
1786103516 94
1786103521 94
1786103526 94
1786103531 94
1786103536 94
1786103541 94
1786103546 94
1786103551 94
1786103556 94
```
</details>

---

