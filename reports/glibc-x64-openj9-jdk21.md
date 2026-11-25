---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:28:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 48-61 cores)</summary>

```
1795641784 61
1795641789 61
1795641794 61
1795641799 61
1795641804 61
1795641809 61
1795641814 61
1795641819 61
1795641824 61
1795641829 61
1795641834 61
1795641839 61
1795641844 53
1795641849 53
1795641854 53
1795641859 53
1795641864 53
1795641869 53
1795641874 53
1795641879 53
```
</details>

---

