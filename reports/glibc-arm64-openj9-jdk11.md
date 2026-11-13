---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 08:55:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794577837 43
1794577842 48
1794577847 48
1794577852 48
1794577857 48
1794577862 48
1794577867 48
1794577872 48
1794577877 48
1794577882 48
1794577887 48
1794577892 48
1794577897 48
1794577902 48
1794577907 48
1794577912 48
1794577917 48
1794577922 48
1794577927 48
1794577932 48
```
</details>

---

