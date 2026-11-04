---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 00:07:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 10 |
| Allocations | 125 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793768565 48
1793768570 48
1793768575 43
1793768580 43
1793768585 43
1793768590 43
1793768595 43
1793768600 43
1793768605 43
1793768610 43
1793768615 43
1793768620 43
1793768625 43
1793768630 43
1793768635 43
1793768640 43
1793768645 43
1793768650 48
1793768655 48
1793768660 48
```
</details>

---

