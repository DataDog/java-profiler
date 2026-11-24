---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 06:19:50 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 23-32 cores)</summary>

```
1795518894 30
1795518899 30
1795518904 30
1795518909 30
1795518914 30
1795518919 30
1795518924 30
1795518929 30
1795518934 32
1795518939 32
1795518944 32
1795518949 32
1795518954 32
1795518959 32
1795518964 32
1795518969 32
1795518974 23
1795518979 23
1795518984 23
1795518989 23
```
</details>

---

