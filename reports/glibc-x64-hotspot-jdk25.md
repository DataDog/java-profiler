---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 16:32:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 19-36 cores)</summary>

```
1795382971 32
1795382976 32
1795382981 32
1795382986 32
1795382991 32
1795382996 32
1795383001 32
1795383006 32
1795383011 34
1795383016 34
1795383021 34
1795383026 34
1795383031 34
1795383036 34
1795383041 34
1795383046 36
1795383051 36
1795383056 36
1795383061 36
1795383066 36
```
</details>

---

