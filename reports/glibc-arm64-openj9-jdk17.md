---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 06:43:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 36-44 cores)</summary>

```
1790678320 36
1790678325 36
1790678330 36
1790678335 36
1790678340 36
1790678345 36
1790678350 36
1790678355 36
1790678360 44
1790678365 44
1790678370 44
1790678375 44
1790678380 44
1790678385 44
1790678390 44
1790678395 44
1790678400 44
1790678405 44
1790678410 44
1790678415 44
```
</details>

---

