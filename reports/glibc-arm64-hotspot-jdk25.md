---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 07:14:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 18-20 cores)</summary>

```
1793880518 18
1793880523 18
1793880528 18
1793880533 18
1793880538 18
1793880543 18
1793880548 18
1793880553 20
1793880558 20
1793880563 20
1793880568 20
1793880573 20
1793880578 20
1793880583 20
1793880588 20
1793880593 20
1793880598 20
1793880603 20
1793880608 20
1793880613 20
```
</details>

---

