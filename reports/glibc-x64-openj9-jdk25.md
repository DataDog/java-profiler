---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-28 12:10:03 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 27-37 cores)</summary>

```
1777392357 27
1777392362 27
1777392367 27
1777392372 32
1777392377 32
1777392382 32
1777392387 32
1777392392 32
1777392397 32
1777392402 32
1777392407 32
1777392412 36
1777392417 36
1777392422 33
1777392427 33
1777392432 33
1777392437 33
1777392442 33
1777392447 33
1777392452 33
```
</details>

---

