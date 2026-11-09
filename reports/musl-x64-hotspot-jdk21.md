---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 07:22:32 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 970 |
| Sample Rate | 16.17/sec |
| Health Score | 1011% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 24-48 cores)</summary>

```
1794226686 43
1794226691 43
1794226696 43
1794226701 43
1794226706 43
1794226711 48
1794226716 48
1794226721 48
1794226726 48
1794226731 48
1794226736 48
1794226741 24
1794226746 24
1794226751 24
1794226756 24
1794226761 24
1794226766 24
1794226771 24
1794226776 24
1794226781 24
```
</details>

---

