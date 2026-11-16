---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 11:32:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794846385 51
1794846390 51
1794846395 51
1794846400 51
1794846405 51
1794846410 51
1794846415 51
1794846420 51
1794846425 51
1794846430 51
1794846435 51
1794846440 51
1794846445 51
1794846450 51
1794846455 51
1794846460 51
1794846465 46
1794846470 46
1794846475 46
1794846480 46
```
</details>

---

