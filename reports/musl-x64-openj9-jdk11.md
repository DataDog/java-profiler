---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-25 00:57:36 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 9 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 61-81 cores)</summary>

```
1787633633 77
1787633638 77
1787633643 79
1787633648 79
1787633653 81
1787633658 81
1787633663 61
1787633668 61
1787633673 61
1787633678 61
1787633683 61
1787633688 61
1787633693 61
1787633698 61
1787633703 61
1787633708 61
1787633713 61
1787633718 61
1787633723 61
1787633728 61
```
</details>

---

