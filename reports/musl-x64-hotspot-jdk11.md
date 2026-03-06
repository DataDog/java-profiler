---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-06 07:48:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (6 unique values: 15-29 cores)</summary>

```
1772800936 15
1772800941 15
1772800946 15
1772800951 15
1772800956 15
1772800961 15
1772800966 15
1772800971 29
1772800976 29
1772800981 26
1772800986 26
1772800991 26
1772800996 26
1772801001 26
1772801006 26
1772801011 23
1772801016 23
1772801021 23
1772801026 23
1772801031 23
```
</details>

---

