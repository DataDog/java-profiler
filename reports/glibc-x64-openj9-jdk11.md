---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 05:49:51 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 939 |
| Sample Rate | 15.65/sec |
| Health Score | 978% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (6 unique values: 26-39 cores)</summary>

```
1778579066 26
1778579071 26
1778579076 26
1778579081 31
1778579086 31
1778579091 31
1778579096 31
1778579101 31
1778579106 31
1778579111 31
1778579116 31
1778579121 31
1778579126 31
1778579131 31
1778579136 31
1778579141 31
1778579146 29
1778579151 29
1778579156 29
1778579161 29
```
</details>

---

