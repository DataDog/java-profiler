---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-17 12:00:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776441386 64
1776441391 64
1776441396 64
1776441401 64
1776441406 64
1776441411 64
1776441416 64
1776441421 64
1776441426 64
1776441431 64
1776441436 64
1776441441 64
1776441446 64
1776441451 64
1776441457 64
1776441462 64
1776441467 64
1776441472 64
1776441477 64
1776441482 64
```
</details>

---

