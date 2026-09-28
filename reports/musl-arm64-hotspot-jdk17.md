---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-28 07:58:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (4 unique values: 51-59 cores)</summary>

```
1790596472 52
1790596478 57
1790596483 57
1790596488 57
1790596493 57
1790596498 57
1790596503 57
1790596508 59
1790596513 59
1790596518 51
1790596523 51
1790596528 51
1790596533 51
1790596538 51
1790596543 51
1790596548 51
1790596553 51
1790596558 51
1790596563 51
1790596568 51
```
</details>

---

