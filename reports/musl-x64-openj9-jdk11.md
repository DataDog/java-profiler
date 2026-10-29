---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 11:53:30 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 62-73 cores)</summary>

```
1793288675 73
1793288680 73
1793288685 73
1793288690 73
1793288695 73
1793288700 73
1793288705 73
1793288710 73
1793288715 73
1793288720 73
1793288725 64
1793288730 64
1793288735 64
1793288740 64
1793288745 64
1793288750 62
1793288755 62
1793288760 62
1793288765 62
1793288770 62
```
</details>

---

