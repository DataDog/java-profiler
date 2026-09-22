---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 16:59:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 19-49 cores)</summary>

```
1790110453 49
1790110458 49
1790110463 49
1790110468 49
1790110473 49
1790110478 49
1790110483 49
1790110488 49
1790110493 49
1790110498 49
1790110503 49
1790110508 49
1790110513 49
1790110518 49
1790110523 49
1790110528 34
1790110533 34
1790110538 34
1790110543 34
1790110548 34
```
</details>

---

