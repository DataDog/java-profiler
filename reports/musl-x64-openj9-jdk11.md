---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 14:19:37 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 857 |
| Sample Rate | 14.28/sec |
| Health Score | 892% |
| Threads | 9 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1794597292 94
1794597297 94
1794597302 94
1794597307 94
1794597312 94
1794597317 94
1794597322 94
1794597327 94
1794597332 94
1794597337 94
1794597342 94
1794597347 94
1794597352 94
1794597357 94
1794597362 94
1794597367 90
1794597372 90
1794597377 90
1794597382 90
1794597387 90
```
</details>

---

