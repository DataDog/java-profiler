---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 06:43:04 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1790678300 96
1790678305 96
1790678310 96
1790678315 76
1790678320 76
1790678325 76
1790678330 76
1790678335 76
1790678340 76
1790678345 76
1790678350 76
1790678355 76
1790678360 76
1790678365 76
1790678370 76
1790678375 76
1790678380 76
1790678385 76
1790678390 76
1790678395 76
```
</details>

---

