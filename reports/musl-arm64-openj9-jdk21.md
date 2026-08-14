---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-14 01:01:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1786683341 64
1786683346 64
1786683351 64
1786683356 64
1786683361 64
1786683366 64
1786683371 64
1786683376 64
1786683381 64
1786683386 62
1786683391 62
1786683396 62
1786683401 62
1786683406 62
1786683411 62
1786683416 62
1786683421 62
1786683426 62
1786683431 62
1786683436 62
```
</details>

---

