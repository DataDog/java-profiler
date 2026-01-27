---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-27 09:51:04 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 16.33/sec |
| Health Score | 1021% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 21.03/sec |
| Health Score | 1314% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1769524879 32
1769524884 32
1769524889 32
1769524894 32
1769524899 32
1769524904 32
1769524909 32
1769524914 32
1769524919 32
1769524924 32
1769524929 32
1769524934 32
1769524939 32
1769524944 27
1769524949 27
1769524954 27
1769524959 27
1769524964 27
1769524969 27
1769524974 27
```
</details>

---

