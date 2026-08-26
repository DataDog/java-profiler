---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-26 07:12:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1787742468 20
1787742473 20
1787742478 20
1787742483 20
1787742488 20
1787742493 20
1787742498 20
1787742503 22
1787742508 22
1787742513 22
1787742518 22
1787742523 22
1787742528 22
1787742533 22
1787742538 22
1787742543 22
1787742548 22
1787742553 22
1787742558 22
1787742563 22
```
</details>

---

