---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 07:21:17 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 12-34 cores)</summary>

```
1789989478 14
1789989483 14
1789989488 14
1789989493 14
1789989498 14
1789989503 14
1789989508 14
1789989513 14
1789989518 12
1789989523 12
1789989528 12
1789989533 12
1789989538 12
1789989543 12
1789989548 12
1789989553 32
1789989558 32
1789989563 32
1789989568 32
1789989573 34
```
</details>

---

