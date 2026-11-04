---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:22:58 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 55-60 cores)</summary>

```
1793830714 55
1793830719 60
1793830724 60
1793830729 60
1793830734 60
1793830739 60
1793830744 60
1793830749 60
1793830754 60
1793830759 60
1793830764 60
1793830769 60
1793830774 60
1793830779 60
1793830784 60
1793830789 60
1793830794 60
1793830799 60
1793830804 60
1793830809 60
```
</details>

---

