---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 09:27:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 11 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 67-78 cores)</summary>

```
1794234138 67
1794234143 67
1794234148 67
1794234153 67
1794234158 67
1794234163 67
1794234168 67
1794234173 75
1794234178 75
1794234183 75
1794234188 75
1794234193 75
1794234198 75
1794234203 75
1794234208 75
1794234213 75
1794234218 75
1794234223 75
1794234228 75
1794234233 75
```
</details>

---

