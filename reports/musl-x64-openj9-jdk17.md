---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-30 10:06:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 869 |
| Sample Rate | 14.48/sec |
| Health Score | 905% |
| Threads | 12 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (6 unique values: 69-80 cores)</summary>

```
1777557720 80
1777557725 80
1777557730 80
1777557735 80
1777557740 80
1777557745 80
1777557750 77
1777557755 77
1777557760 77
1777557765 77
1777557770 70
1777557775 70
1777557780 70
1777557785 69
1777557790 69
1777557795 69
1777557800 71
1777557805 71
1777557810 71
1777557815 71
```
</details>

---

