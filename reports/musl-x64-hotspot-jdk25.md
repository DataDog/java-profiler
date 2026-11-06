---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 16:43:57 EST

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
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 810 |
| Sample Rate | 13.50/sec |
| Health Score | 844% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1794001091 64
1794001096 64
1794001101 64
1794001106 64
1794001111 64
1794001116 64
1794001121 62
1794001126 62
1794001131 62
1794001136 62
1794001141 62
1794001146 62
1794001151 62
1794001156 62
1794001161 62
1794001166 62
1794001171 62
1794001176 62
1794001181 62
1794001186 62
```
</details>

---

