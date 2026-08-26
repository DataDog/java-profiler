---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-26 09:45:35 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 53-61 cores)</summary>

```
1787751588 59
1787751593 59
1787751598 59
1787751603 59
1787751608 61
1787751613 61
1787751618 61
1787751623 61
1787751628 61
1787751633 61
1787751638 59
1787751643 59
1787751648 59
1787751653 57
1787751658 57
1787751663 57
1787751668 57
1787751673 57
1787751678 57
1787751683 53
```
</details>

---

