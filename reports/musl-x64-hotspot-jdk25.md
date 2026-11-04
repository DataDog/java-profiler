---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 13:32:34 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 61-64 cores)</summary>

```
1793816872 64
1793816877 64
1793816882 64
1793816887 64
1793816892 64
1793816897 64
1793816902 61
1793816907 61
1793816912 61
1793816917 61
1793816922 61
1793816927 61
1793816932 61
1793816937 61
1793816942 61
1793816947 61
1793816952 61
1793816957 61
1793816962 61
1793816967 61
```
</details>

---

