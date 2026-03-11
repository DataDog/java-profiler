---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 08:50:42 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 18-23 cores)</summary>

```
1773233038 19
1773233043 19
1773233048 19
1773233053 19
1773233058 18
1773233063 18
1773233068 21
1773233073 21
1773233078 20
1773233083 20
1773233088 20
1773233093 21
1773233098 21
1773233103 21
1773233108 21
1773233113 21
1773233118 21
1773233123 23
1773233128 23
1773233133 23
```
</details>

---

