---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 08:17:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 19.87/sec |
| Health Score | 1242% |
| Threads | 10 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 857 |
| Sample Rate | 28.57/sec |
| Health Score | 1786% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1769692263 32
1769692268 32
1769692273 32
1769692278 32
1769692283 32
1769692288 32
1769692293 32
1769692298 32
1769692303 32
1769692308 32
1769692313 32
1769692318 32
1769692323 32
1769692328 32
1769692333 32
1769692338 32
1769692343 32
1769692348 27
1769692353 27
1769692358 27
```
</details>

---

