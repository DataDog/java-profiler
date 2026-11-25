---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:08:09 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 49-55 cores)</summary>

```
1795618869 55
1795618874 55
1795618879 55
1795618884 55
1795618889 55
1795618894 55
1795618899 55
1795618904 55
1795618909 55
1795618914 55
1795618919 55
1795618924 55
1795618929 55
1795618934 55
1795618939 55
1795618944 55
1795618949 55
1795618954 55
1795618959 53
1795618964 53
```
</details>

---

