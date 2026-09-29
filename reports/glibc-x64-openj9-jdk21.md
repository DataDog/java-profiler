---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-29 06:43:04 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 11 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (4 unique values: 65-92 cores)</summary>

```
1790678295 65
1790678300 65
1790678305 65
1790678310 85
1790678315 85
1790678320 81
1790678325 81
1790678330 81
1790678335 81
1790678340 81
1790678345 81
1790678350 81
1790678355 81
1790678360 81
1790678365 81
1790678370 81
1790678375 81
1790678380 81
1790678385 81
1790678390 81
```
</details>

---

