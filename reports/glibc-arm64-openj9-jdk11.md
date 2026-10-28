---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 20:01:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793145493 48
1793145498 48
1793145503 48
1793145508 48
1793145513 48
1793145518 48
1793145523 48
1793145528 48
1793145533 48
1793145538 48
1793145543 48
1793145548 48
1793145553 48
1793145558 48
1793145563 48
1793145568 48
1793145573 48
1793145578 48
1793145583 48
1793145588 36
```
</details>

---

