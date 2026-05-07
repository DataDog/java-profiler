---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 10:58:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 78-87 cores)</summary>

```
1778165628 81
1778165633 81
1778165638 87
1778165643 87
1778165648 87
1778165653 87
1778165658 87
1778165663 87
1778165668 87
1778165673 87
1778165678 87
1778165683 87
1778165688 87
1778165693 87
1778165698 87
1778165703 87
1778165708 87
1778165713 82
1778165718 82
1778165723 82
```
</details>

---

