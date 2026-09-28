---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-28 10:16:37 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1790604658 76
1790604663 76
1790604668 76
1790604673 76
1790604678 76
1790604683 76
1790604688 74
1790604693 74
1790604698 74
1790604703 74
1790604708 74
1790604713 74
1790604719 74
1790604724 74
1790604729 76
1790604734 76
1790604739 76
1790604744 76
1790604749 76
1790604754 76
```
</details>

---

