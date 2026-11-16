---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-15 19:49:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 71-79 cores)</summary>

```
1794789916 79
1794789921 79
1794789926 79
1794789931 79
1794789936 79
1794789941 79
1794789946 79
1794789951 79
1794789956 71
1794789961 71
1794789966 71
1794789971 71
1794789976 73
1794789981 73
1794789986 73
1794789991 73
1794789996 73
1794790001 73
1794790006 73
1794790011 73
```
</details>

---

