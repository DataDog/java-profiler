---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-07 10:58:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (8 unique values: 73-88 cores)</summary>

```
1778165578 80
1778165583 80
1778165588 80
1778165593 82
1778165598 82
1778165603 82
1778165608 82
1778165613 82
1778165618 82
1778165623 82
1778165628 82
1778165633 82
1778165638 84
1778165643 84
1778165648 84
1778165653 84
1778165658 84
1778165663 88
1778165668 88
1778165673 83
```
</details>

---

