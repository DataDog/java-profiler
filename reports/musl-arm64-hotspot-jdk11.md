---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 05:58:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793789582 48
1793789587 48
1793789592 48
1793789597 48
1793789602 48
1793789607 48
1793789612 48
1793789617 48
1793789622 48
1793789627 48
1793789632 48
1793789637 48
1793789642 48
1793789647 48
1793789652 48
1793789657 48
1793789662 48
1793789667 48
1793789672 48
1793789677 48
```
</details>

---

