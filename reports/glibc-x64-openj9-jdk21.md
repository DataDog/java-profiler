---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-11 05:27:47 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1773220908 32
1773220913 32
1773220918 32
1773220923 32
1773220928 32
1773220933 32
1773220938 32
1773220943 32
1773220948 32
1773220953 32
1773220958 32
1773220963 32
1773220968 26
1773220973 26
1773220978 26
1773220983 26
1773220988 26
1773220993 26
1773220998 26
1773221003 26
```
</details>

---

