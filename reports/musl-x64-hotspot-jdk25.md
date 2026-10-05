---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-05 05:52:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 12 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 51-73 cores)</summary>

```
1791193588 51
1791193593 51
1791193598 73
1791193603 73
1791193608 65
1791193613 65
1791193618 65
1791193623 65
1791193628 65
1791193633 65
1791193638 65
1791193643 65
1791193648 65
1791193653 65
1791193658 65
1791193663 65
1791193668 65
1791193673 65
1791193678 65
1791193683 65
```
</details>

---

