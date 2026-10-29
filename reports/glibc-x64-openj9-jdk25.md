---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 13:19:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (3 unique values: 86-93 cores)</summary>

```
1793294031 86
1793294036 86
1793294041 86
1793294046 86
1793294051 86
1793294056 86
1793294061 86
1793294066 86
1793294071 86
1793294076 91
1793294081 91
1793294086 91
1793294091 91
1793294096 93
1793294101 93
1793294106 93
1793294111 93
1793294116 93
1793294121 93
1793294126 93
```
</details>

---

