---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 08:56:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 64-87 cores)</summary>

```
1794318680 64
1794318685 64
1794318690 64
1794318695 82
1794318700 82
1794318705 82
1794318710 82
1794318715 82
1794318720 82
1794318725 82
1794318730 82
1794318735 82
1794318741 82
1794318746 82
1794318751 82
1794318756 82
1794318761 87
1794318766 87
1794318771 87
1794318776 87
```
</details>

---

