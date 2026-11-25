---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:08:10 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 48-52 cores)</summary>

```
1795618883 50
1795618888 48
1795618893 48
1795618898 50
1795618903 50
1795618908 50
1795618914 50
1795618919 50
1795618924 50
1795618929 50
1795618934 50
1795618939 50
1795618944 50
1795618949 50
1795618954 50
1795618959 50
1795618964 52
1795618969 52
1795618974 52
1795618979 52
```
</details>

---

