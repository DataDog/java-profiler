---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 12:10:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 806 |
| Sample Rate | 13.43/sec |
| Health Score | 839% |
| Threads | 9 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (2 unique values: 55-56 cores)</summary>

```
1790179508 56
1790179513 56
1790179518 56
1790179523 56
1790179528 56
1790179533 56
1790179538 56
1790179543 56
1790179548 56
1790179553 56
1790179558 56
1790179563 56
1790179568 56
1790179573 56
1790179578 56
1790179583 56
1790179588 56
1790179593 56
1790179598 56
1790179603 55
```
</details>

---

