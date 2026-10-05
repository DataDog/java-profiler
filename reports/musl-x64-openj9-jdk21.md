---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 05:52:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 10 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1791193613 96
1791193618 96
1791193623 96
1791193628 94
1791193633 94
1791193638 94
1791193643 94
1791193648 94
1791193653 94
1791193658 94
1791193663 94
1791193668 94
1791193673 94
1791193678 94
1791193683 92
1791193688 92
1791193693 92
1791193698 92
1791193703 92
1791193708 92
```
</details>

---

