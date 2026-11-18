---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:03:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (4 unique values: 55-70 cores)</summary>

```
1795013871 59
1795013876 59
1795013881 57
1795013886 57
1795013891 59
1795013896 59
1795013901 59
1795013906 59
1795013911 55
1795013916 55
1795013921 55
1795013926 55
1795013931 55
1795013936 70
1795013941 70
1795013946 70
1795013951 70
1795013956 70
1795013961 70
1795013966 70
```
</details>

---

