---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 14:03:02 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 16-20 cores)</summary>

```
1786471106 18
1786471111 18
1786471116 16
1786471121 16
1786471126 18
1786471131 18
1786471136 20
1786471141 20
1786471146 20
1786471151 20
1786471156 20
1786471161 20
1786471166 20
1786471171 20
1786471176 20
1786471181 20
1786471186 20
1786471191 20
1786471196 20
1786471201 20
```
</details>

---

