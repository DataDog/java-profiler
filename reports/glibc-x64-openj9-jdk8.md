---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-12 13:21:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 86-93 cores)</summary>

```
1794507367 93
1794507372 93
1794507377 93
1794507382 93
1794507387 93
1794507392 93
1794507397 86
1794507402 86
1794507407 86
1794507412 86
1794507417 86
1794507422 86
1794507427 86
1794507432 86
1794507437 86
1794507442 86
1794507447 86
1794507452 86
1794507457 86
1794507462 86
```
</details>

---

