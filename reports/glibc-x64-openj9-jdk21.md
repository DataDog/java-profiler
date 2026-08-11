---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 14:03:02 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 20-25 cores)</summary>

```
1786471095 25
1786471100 25
1786471105 25
1786471110 25
1786471115 25
1786471120 25
1786471125 25
1786471130 25
1786471135 25
1786471140 23
1786471145 23
1786471150 23
1786471155 23
1786471160 23
1786471165 23
1786471170 23
1786471175 23
1786471180 23
1786471185 23
1786471190 25
```
</details>

---

