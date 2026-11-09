---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 09:27:56 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 429 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1794234143 59
1794234148 59
1794234153 59
1794234158 59
1794234163 59
1794234168 59
1794234173 59
1794234178 59
1794234183 59
1794234188 61
1794234193 61
1794234198 61
1794234203 61
1794234208 61
1794234213 61
1794234218 61
1794234223 61
1794234228 61
1794234233 61
1794234238 61
```
</details>

---

