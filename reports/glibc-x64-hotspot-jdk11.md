---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-06 07:48:04 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 911 |
| Sample Rate | 15.18/sec |
| Health Score | 949% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 52-56 cores)</summary>

```
1772800941 56
1772800946 56
1772800951 56
1772800956 56
1772800961 56
1772800966 56
1772800971 56
1772800976 56
1772800981 52
1772800986 52
1772800991 54
1772800996 54
1772801001 54
1772801006 54
1772801011 54
1772801016 54
1772801021 54
1772801026 54
1772801031 54
1772801036 54
```
</details>

---

