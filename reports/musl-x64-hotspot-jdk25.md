---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 07:22:32 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 12 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 56-61 cores)</summary>

```
1794226681 56
1794226686 56
1794226691 56
1794226696 56
1794226701 56
1794226706 56
1794226711 56
1794226716 56
1794226721 56
1794226726 61
1794226731 61
1794226736 58
1794226741 58
1794226746 58
1794226751 58
1794226756 58
1794226761 58
1794226766 58
1794226771 58
1794226776 58
```
</details>

---

