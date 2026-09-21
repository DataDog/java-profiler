---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 15:32:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 49-57 cores)</summary>

```
1790018789 49
1790018794 49
1790018799 49
1790018804 49
1790018809 49
1790018814 49
1790018819 49
1790018824 49
1790018829 49
1790018834 49
1790018839 49
1790018844 49
1790018849 49
1790018854 49
1790018859 49
1790018864 49
1790018869 57
1790018874 57
1790018879 57
1790018884 57
```
</details>

---

