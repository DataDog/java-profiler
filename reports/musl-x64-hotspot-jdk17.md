---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-27 10:22:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 23.40/sec |
| Health Score | 1462% |
| Threads | 11 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1769526906 39
1769526911 39
1769526916 39
1769526921 39
1769526926 39
1769526931 39
1769526936 39
1769526941 44
1769526946 44
1769526951 44
1769526956 44
1769526961 44
1769526966 44
1769526971 44
1769526976 44
1769526981 44
1769526986 44
1769526991 44
1769526996 44
1769527001 44
```
</details>

---

