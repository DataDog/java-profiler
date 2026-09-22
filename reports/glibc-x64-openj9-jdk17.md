---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 13:10:30 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 70-75 cores)</summary>

```
1790096695 71
1790096700 71
1790096705 71
1790096710 71
1790096715 71
1790096720 71
1790096725 71
1790096730 71
1790096735 70
1790096740 70
1790096745 70
1790096750 70
1790096755 70
1790096760 70
1790096765 72
1790096770 72
1790096775 72
1790096780 72
1790096785 72
1790096790 70
```
</details>

---

