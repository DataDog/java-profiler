---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 12:12:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 14 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (3 unique values: 36-51 cores)</summary>

```
1794589690 36
1794589695 36
1794589700 36
1794589705 36
1794589710 36
1794589715 46
1794589720 46
1794589725 46
1794589730 46
1794589735 51
1794589740 51
1794589745 51
1794589750 51
1794589755 51
1794589760 51
1794589765 51
1794589770 51
1794589775 51
1794589780 51
1794589785 51
```
</details>

---

