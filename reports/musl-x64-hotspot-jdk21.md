---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 12:11:47 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1029 |
| Sample Rate | 17.15/sec |
| Health Score | 1072% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 75-77 cores)</summary>

```
1794243956 77
1794243961 75
1794243966 75
1794243971 77
1794243976 77
1794243981 77
1794243986 77
1794243991 77
1794243996 77
1794244001 77
1794244006 77
1794244011 77
1794244016 77
1794244021 77
1794244026 77
1794244031 77
1794244036 77
1794244041 75
1794244046 75
1794244051 75
```
</details>

---

