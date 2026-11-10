---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 06:47:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1794310981 49
1794310986 49
1794310991 49
1794310996 49
1794311001 49
1794311006 49
1794311011 49
1794311016 49
1794311021 47
1794311026 47
1794311031 47
1794311036 47
1794311041 47
1794311046 47
1794311051 51
1794311056 51
1794311061 51
1794311066 51
1794311071 49
1794311076 49
```
</details>

---

