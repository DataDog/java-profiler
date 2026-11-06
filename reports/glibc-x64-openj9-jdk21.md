---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 20:23:05 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 56-62 cores)</summary>

```
1793927869 62
1793927874 62
1793927879 62
1793927884 62
1793927889 62
1793927894 62
1793927899 62
1793927904 62
1793927909 62
1793927914 62
1793927919 62
1793927924 62
1793927929 62
1793927934 62
1793927939 62
1793927944 62
1793927949 62
1793927954 62
1793927959 60
1793927964 60
```
</details>

---

