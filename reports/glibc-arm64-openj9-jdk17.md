---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 17:22:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1793830764 44
1793830769 44
1793830774 44
1793830779 44
1793830784 48
1793830789 48
1793830794 48
1793830799 48
1793830804 48
1793830809 48
1793830814 48
1793830819 48
1793830824 48
1793830829 48
1793830834 48
1793830839 48
1793830844 48
1793830849 48
1793830854 48
1793830859 48
```
</details>

---

