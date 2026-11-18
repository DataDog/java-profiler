---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 07:34:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 945 |
| Sample Rate | 15.75/sec |
| Health Score | 984% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 30-38 cores)</summary>

```
1795004961 30
1795004966 30
1795004971 30
1795004976 30
1795004981 30
1795004986 30
1795004991 30
1795004996 30
1795005001 30
1795005006 30
1795005011 30
1795005016 30
1795005021 30
1795005026 38
1795005031 38
1795005036 38
1795005041 38
1795005046 38
1795005051 38
1795005056 38
```
</details>

---

