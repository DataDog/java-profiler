---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-11 11:40:58 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 10 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 13 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (7 unique values: 81-94 cores)</summary>

```
1770827623 94
1770827628 92
1770827633 92
1770827638 92
1770827643 92
1770827648 87
1770827653 87
1770827658 87
1770827663 92
1770827668 92
1770827673 90
1770827678 90
1770827683 90
1770827688 84
1770827693 84
1770827698 86
1770827703 86
1770827708 81
1770827713 81
1770827718 81
```
</details>

---

