---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-16 12:37:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 77-82 cores)</summary>

```
1794850040 82
1794850045 82
1794850050 81
1794850055 81
1794850060 81
1794850065 81
1794850071 81
1794850076 81
1794850081 81
1794850086 81
1794850091 81
1794850096 77
1794850101 77
1794850106 77
1794850111 77
1794850116 77
1794850121 77
1794850126 77
1794850131 77
1794850136 77
```
</details>

---

