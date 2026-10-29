---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 13:49:38 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1793295794 62
1793295799 62
1793295804 62
1793295809 62
1793295814 62
1793295819 62
1793295824 62
1793295829 62
1793295834 62
1793295839 62
1793295844 62
1793295849 62
1793295854 62
1793295859 62
1793295864 62
1793295869 62
1793295874 62
1793295879 62
1793295884 64
1793295889 64
```
</details>

---

