---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 09:07:12 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 12 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 32-36 cores)</summary>

```
1787230946 34
1787230951 34
1787230956 36
1787230961 36
1787230966 32
1787230971 32
1787230976 32
1787230981 32
1787230986 32
1787230991 34
1787230996 34
1787231001 36
1787231006 36
1787231011 36
1787231016 36
1787231021 34
1787231026 34
1787231031 34
1787231036 34
1787231041 34
```
</details>

---

