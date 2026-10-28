---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:43:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 421 |
| Sample Rate | 7.02/sec |
| Health Score | 439% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (3 unique values: 9-12 cores)</summary>

```
1793187478 10
1793187483 10
1793187488 10
1793187493 10
1793187498 10
1793187503 10
1793187508 10
1793187513 12
1793187518 12
1793187523 12
1793187528 12
1793187533 12
1793187538 12
1793187543 9
1793187548 9
1793187553 9
1793187558 9
1793187563 9
1793187568 9
1793187573 9
```
</details>

---

