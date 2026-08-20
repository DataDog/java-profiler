---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 07:52:37 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 11 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787226448 48
1787226453 48
1787226458 43
1787226463 43
1787226468 43
1787226473 43
1787226478 43
1787226483 43
1787226488 43
1787226493 43
1787226498 43
1787226503 43
1787226508 43
1787226513 48
1787226518 48
1787226523 48
1787226528 48
1787226533 48
1787226538 48
1787226543 48
```
</details>

---

