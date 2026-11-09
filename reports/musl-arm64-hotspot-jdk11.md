---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 14:48:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 302 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 11 |
| Allocations | 124 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 14 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (3 unique values: 34-51 cores)</summary>

```
1794253457 51
1794253462 51
1794253467 51
1794253472 51
1794253477 51
1794253482 51
1794253487 51
1794253492 51
1794253497 51
1794253502 51
1794253507 51
1794253512 39
1794253517 39
1794253522 39
1794253527 39
1794253532 39
1794253537 39
1794253542 39
1794253547 39
1794253552 39
```
</details>

---

