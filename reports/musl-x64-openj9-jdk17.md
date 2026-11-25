---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:21:58 EST

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 5 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 13-22 cores)</summary>

```
1795641288 15
1795641293 13
1795641298 13
1795641303 13
1795641308 13
1795641313 22
1795641318 22
1795641323 22
1795641328 22
1795641333 22
1795641338 22
1795641343 22
1795641348 22
1795641353 22
1795641358 22
1795641363 22
1795641368 22
1795641373 22
1795641378 22
1795641383 22
```
</details>

---

