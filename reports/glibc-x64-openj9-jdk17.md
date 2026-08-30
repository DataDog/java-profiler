---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-30 05:49:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 8-10 cores)</summary>

```
1788083090 8
1788083095 8
1788083100 8
1788083105 8
1788083110 8
1788083115 8
1788083120 8
1788083125 8
1788083130 10
1788083135 10
1788083140 10
1788083145 10
1788083150 10
1788083155 10
1788083160 10
1788083165 10
1788083170 10
1788083175 10
1788083180 10
1788083185 10
```
</details>

---

