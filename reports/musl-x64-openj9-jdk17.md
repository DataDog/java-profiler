---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 08:31:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 67-78 cores)</summary>

```
1795008233 67
1795008238 67
1795008243 67
1795008248 67
1795008253 77
1795008258 77
1795008263 77
1795008268 68
1795008273 68
1795008278 68
1795008283 68
1795008288 68
1795008293 68
1795008298 68
1795008303 68
1795008308 78
1795008313 78
1795008318 78
1795008323 78
1795008328 78
```
</details>

---

