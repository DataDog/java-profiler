---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 17:22:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 376 |
| Sample Rate | 6.27/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 46-50 cores)</summary>

```
1793830754 50
1793830759 50
1793830764 50
1793830769 50
1793830774 50
1793830779 50
1793830784 50
1793830789 50
1793830794 50
1793830799 48
1793830804 48
1793830809 46
1793830814 46
1793830819 46
1793830824 46
1793830829 48
1793830834 48
1793830839 48
1793830844 48
1793830849 48
```
</details>

---

