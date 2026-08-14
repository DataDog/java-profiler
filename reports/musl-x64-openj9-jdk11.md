---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-14 01:01:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 8 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 9-17 cores)</summary>

```
1786683287 9
1786683292 9
1786683297 9
1786683302 9
1786683307 9
1786683312 9
1786683317 9
1786683322 9
1786683327 17
1786683332 17
1786683337 17
1786683342 17
1786683347 17
1786683352 17
1786683357 17
1786683362 17
1786683367 17
1786683372 17
1786683377 17
1786683382 17
```
</details>

---

