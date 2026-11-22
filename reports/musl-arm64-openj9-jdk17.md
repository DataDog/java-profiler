---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-22 16:32:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 12 |
| Allocations | 89 |

<details>
<summary>CPU Timeline (3 unique values: 23-33 cores)</summary>

```
1795382916 33
1795382921 33
1795382926 33
1795382931 33
1795382936 33
1795382941 33
1795382946 33
1795382951 33
1795382956 33
1795382961 33
1795382966 33
1795382971 33
1795382976 33
1795382981 33
1795382986 28
1795382991 28
1795382996 28
1795383001 28
1795383006 23
1795383011 23
```
</details>

---

