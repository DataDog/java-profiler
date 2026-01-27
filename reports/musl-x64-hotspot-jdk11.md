---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-27 10:22:46 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 19.70/sec |
| Health Score | 1231% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 25.83/sec |
| Health Score | 1614% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1769526914 26
1769526919 26
1769526924 28
1769526929 28
1769526934 32
1769526939 32
1769526944 29
1769526949 29
1769526954 29
1769526959 29
1769526964 29
1769526969 29
1769526974 29
1769526979 29
1769526984 29
1769526989 29
1769526994 29
1769526999 29
1769527004 29
1769527009 29
```
</details>

---

