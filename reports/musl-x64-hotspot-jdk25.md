---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 10:08:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (8 unique values: 33-45 cores)</summary>

```
1790690602 42
1790690607 42
1790690612 42
1790690617 42
1790690622 40
1790690627 40
1790690632 40
1790690637 43
1790690642 43
1790690647 45
1790690652 45
1790690657 43
1790690662 43
1790690667 43
1790690672 33
1790690677 33
1790690682 35
1790690687 35
1790690692 39
1790690697 39
```
</details>

---

