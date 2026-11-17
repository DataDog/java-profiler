---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 10:58:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 901 |
| Sample Rate | 15.02/sec |
| Health Score | 939% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 64-71 cores)</summary>

```
1794930740 71
1794930745 71
1794930750 71
1794930755 71
1794930760 71
1794930765 71
1794930770 71
1794930775 71
1794930780 71
1794930785 69
1794930790 69
1794930795 69
1794930800 69
1794930805 69
1794930810 69
1794930815 69
1794930820 69
1794930825 69
1794930830 69
1794930835 69
```
</details>

---

