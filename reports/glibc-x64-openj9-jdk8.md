---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-26 08:33:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1793017779 46
1793017784 46
1793017789 46
1793017794 46
1793017799 46
1793017804 46
1793017809 46
1793017814 46
1793017819 46
1793017824 46
1793017829 46
1793017834 46
1793017839 46
1793017844 46
1793017849 46
1793017854 46
1793017859 44
1793017864 44
1793017869 44
1793017874 44
```
</details>

---

