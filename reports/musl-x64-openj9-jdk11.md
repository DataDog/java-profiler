---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 10:58:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 59-67 cores)</summary>

```
1778165578 59
1778165583 61
1778165588 61
1778165593 61
1778165598 61
1778165603 65
1778165608 65
1778165613 65
1778165618 65
1778165623 65
1778165628 65
1778165633 65
1778165638 65
1778165643 67
1778165648 67
1778165653 67
1778165658 67
1778165663 67
1778165668 67
1778165673 67
```
</details>

---

