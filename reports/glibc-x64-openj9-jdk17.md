---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 07:23:19 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 92-96 cores)</summary>

```
1787224769 96
1787224774 96
1787224779 96
1787224784 96
1787224789 96
1787224794 96
1787224799 96
1787224804 96
1787224809 96
1787224814 96
1787224819 96
1787224824 96
1787224829 96
1787224834 96
1787224839 96
1787224844 96
1787224849 96
1787224854 96
1787224859 92
1787224864 92
```
</details>

---

