---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:39:43 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 64-78 cores)</summary>

```
1795537829 64
1795537834 64
1795537839 64
1795537844 64
1795537849 64
1795537854 64
1795537859 64
1795537864 64
1795537869 64
1795537874 64
1795537879 64
1795537884 69
1795537889 69
1795537894 69
1795537899 69
1795537904 69
1795537909 69
1795537914 69
1795537919 69
1795537924 69
```
</details>

---

