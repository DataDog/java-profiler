---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 10:44:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 10 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1790087824 50
1790087829 50
1790087834 50
1790087839 50
1790087844 50
1790087849 50
1790087854 50
1790087859 50
1790087864 50
1790087869 50
1790087874 45
1790087879 45
1790087884 45
1790087889 45
1790087894 45
1790087899 45
1790087904 45
1790087909 45
1790087914 45
1790087919 45
```
</details>

---

