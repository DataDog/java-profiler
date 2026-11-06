---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-06 16:43:57 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (5 unique values: 42-51 cores)</summary>

```
1794001096 50
1794001101 50
1794001106 42
1794001111 42
1794001116 44
1794001121 44
1794001126 44
1794001131 44
1794001136 44
1794001141 44
1794001146 44
1794001151 44
1794001156 44
1794001161 44
1794001166 44
1794001171 44
1794001176 44
1794001182 44
1794001187 46
1794001192 46
```
</details>

---

