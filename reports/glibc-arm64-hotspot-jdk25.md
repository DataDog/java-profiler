---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 00:07:57 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793768600 43
1793768605 43
1793768610 43
1793768615 43
1793768620 43
1793768625 43
1793768630 43
1793768635 43
1793768640 43
1793768645 48
1793768650 48
1793768655 48
1793768660 48
1793768665 48
1793768670 48
1793768675 48
1793768680 48
1793768685 48
1793768690 48
1793768695 48
```
</details>

---

