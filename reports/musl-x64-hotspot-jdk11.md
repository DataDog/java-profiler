---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 20:41:36 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794793050 32
1794793055 32
1794793060 32
1794793065 32
1794793070 32
1794793075 32
1794793080 32
1794793085 32
1794793090 32
1794793095 32
1794793100 32
1794793105 32
1794793110 32
1794793115 32
1794793120 32
1794793125 32
1794793130 32
1794793135 32
1794793140 32
1794793145 32
```
</details>

---

