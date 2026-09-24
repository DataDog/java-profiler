---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 09:54:55 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 405 |

<details>
<summary>CPU Timeline (2 unique values: 90-96 cores)</summary>

```
1790257739 90
1790257744 90
1790257749 90
1790257754 90
1790257759 90
1790257764 90
1790257769 90
1790257774 90
1790257779 90
1790257784 90
1790257789 90
1790257794 90
1790257799 90
1790257804 90
1790257809 96
1790257814 96
1790257819 96
1790257824 96
1790257829 96
1790257834 96
```
</details>

---

