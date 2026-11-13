---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 16:17:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1794604404 48
1794604409 48
1794604414 48
1794604419 48
1794604424 43
1794604429 43
1794604434 43
1794604439 43
1794604445 43
1794604450 43
1794604455 43
1794604460 43
1794604465 43
1794604470 41
1794604475 41
1794604480 41
1794604485 41
1794604490 41
1794604495 41
1794604500 41
```
</details>

---

