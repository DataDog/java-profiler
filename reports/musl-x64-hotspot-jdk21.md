---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-06 14:08:08 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 858 |
| Sample Rate | 14.30/sec |
| Health Score | 894% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (6 unique values: 74-92 cores)</summary>

```
1778090394 84
1778090399 84
1778090404 84
1778090409 84
1778090414 88
1778090419 88
1778090424 92
1778090429 92
1778090434 92
1778090439 92
1778090444 92
1778090449 92
1778090454 92
1778090459 89
1778090464 89
1778090469 89
1778090474 89
1778090479 89
1778090484 89
1778090489 89
```
</details>

---

