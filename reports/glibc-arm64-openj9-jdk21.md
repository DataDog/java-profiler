---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-10 05:03:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 13 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 17-19 cores)</summary>

```
1786352347 19
1786352352 19
1786352357 19
1786352362 19
1786352367 19
1786352372 19
1786352377 19
1786352382 19
1786352387 19
1786352392 19
1786352397 19
1786352402 19
1786352407 19
1786352412 19
1786352417 19
1786352422 19
1786352427 19
1786352432 19
1786352437 19
1786352442 19
```
</details>

---

