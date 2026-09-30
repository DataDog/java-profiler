---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 11:36:50 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 71-96 cores)</summary>

```
1790782358 71
1790782363 71
1790782368 71
1790782373 71
1790782378 71
1790782383 71
1790782388 71
1790782393 71
1790782398 71
1790782403 71
1790782408 71
1790782413 71
1790782418 71
1790782423 71
1790782428 71
1790782433 71
1790782438 74
1790782443 74
1790782448 74
1790782453 74
```
</details>

---

