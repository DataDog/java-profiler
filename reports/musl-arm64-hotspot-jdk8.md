---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ❌ FAIL

**Date:** 2026-11-25 07:54:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 4 |
| Sample Rate | 0.07/sec |
| Health Score | 4% |
| Threads | 1 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 33-33 cores)</summary>

```
1795610939 33
1795610944 33
1795610949 33
1795610954 33
1795610959 33
1795610964 33
1795610969 33
1795610974 33
1795610979 33
1795610984 33
1795610989 33
1795610994 33
1795610999 33
1795611004 33
1795611009 33
1795611014 33
1795611019 33
1795611024 33
1795611029 33
1795611034 33
```
</details>

---

