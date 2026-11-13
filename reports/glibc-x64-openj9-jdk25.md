---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 06:01:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 46-64 cores)</summary>

```
1794567356 58
1794567361 58
1794567366 58
1794567371 58
1794567376 58
1794567381 58
1794567386 58
1794567391 58
1794567396 58
1794567401 58
1794567406 58
1794567411 58
1794567416 64
1794567421 64
1794567426 62
1794567431 62
1794567436 62
1794567441 62
1794567446 62
1794567451 62
```
</details>

---

