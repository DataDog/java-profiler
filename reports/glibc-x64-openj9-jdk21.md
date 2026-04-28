---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-28 12:10:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1777392316 27
1777392321 27
1777392326 27
1777392331 27
1777392336 27
1777392341 25
1777392346 25
1777392351 25
1777392356 25
1777392361 27
1777392366 27
1777392371 27
1777392376 27
1777392381 27
1777392386 27
1777392391 27
1777392396 27
1777392401 27
1777392406 27
1777392411 27
```
</details>

---

