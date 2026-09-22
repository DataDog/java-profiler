---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 17:00:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 855 |
| Sample Rate | 14.25/sec |
| Health Score | 891% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 72-81 cores)</summary>

```
1790110473 81
1790110478 81
1790110483 81
1790110488 81
1790110493 81
1790110498 81
1790110503 81
1790110508 81
1790110513 81
1790110518 81
1790110523 81
1790110528 81
1790110533 81
1790110538 81
1790110543 81
1790110548 81
1790110553 81
1790110558 72
1790110563 72
1790110568 72
```
</details>

---

