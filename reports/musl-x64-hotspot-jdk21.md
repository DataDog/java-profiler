---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 17:10:05 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 21 |
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
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 17-21 cores)</summary>

```
1778187903 17
1778187908 17
1778187913 17
1778187918 17
1778187923 17
1778187928 17
1778187933 17
1778187938 17
1778187943 17
1778187948 17
1778187953 17
1778187958 17
1778187963 17
1778187968 21
1778187973 21
1778187978 21
1778187984 21
1778187989 21
1778187994 21
1778187999 21
```
</details>

---

