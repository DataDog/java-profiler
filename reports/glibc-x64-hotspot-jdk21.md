---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-22 15:27:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787426630 66
1787426635 66
1787426640 66
1787426645 66
1787426650 66
1787426655 66
1787426660 66
1787426665 66
1787426670 66
1787426675 66
1787426680 66
1787426685 66
1787426690 66
1787426695 66
1787426700 66
1787426705 66
1787426710 64
1787426715 64
1787426720 64
1787426725 64
```
</details>

---

