---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:22:55 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795641298 29
1795641303 29
1795641308 29
1795641313 29
1795641318 29
1795641323 29
1795641328 29
1795641333 29
1795641338 29
1795641343 34
1795641348 34
1795641353 34
1795641358 34
1795641363 34
1795641368 34
1795641373 34
1795641378 34
1795641383 34
1795641388 34
1795641393 34
```
</details>

---

