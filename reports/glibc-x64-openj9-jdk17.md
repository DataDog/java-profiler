---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 07:06:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (5 unique values: 74-88 cores)</summary>

```
1791543734 86
1791543739 86
1791543744 86
1791543749 86
1791543754 86
1791543759 86
1791543764 86
1791543769 86
1791543774 86
1791543779 86
1791543784 88
1791543789 88
1791543794 76
1791543799 76
1791543804 76
1791543809 76
1791543814 76
1791543819 76
1791543824 74
1791543829 74
```
</details>

---

