---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 11:47:27 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (5 unique values: 62-67 cores)</summary>

```
1793374881 67
1793374886 64
1793374891 64
1793374896 64
1793374901 64
1793374906 64
1793374911 64
1793374916 64
1793374921 64
1793374926 64
1793374931 64
1793374936 64
1793374941 64
1793374946 64
1793374951 64
1793374956 62
1793374961 62
1793374966 62
1793374971 62
1793374976 62
```
</details>

---

