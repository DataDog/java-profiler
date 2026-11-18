---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 09:10:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1795010726 46
1795010731 46
1795010736 46
1795010741 46
1795010746 46
1795010751 46
1795010756 46
1795010761 46
1795010766 46
1795010771 46
1795010776 46
1795010781 46
1795010786 46
1795010791 51
1795010796 51
1795010801 51
1795010806 51
1795010811 51
1795010816 51
1795010821 51
```
</details>

---

