---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 00:01:37 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 33-66 cores)</summary>

```
1795323349 33
1795323354 33
1795323359 33
1795323364 33
1795323369 33
1795323374 33
1795323379 33
1795323384 33
1795323389 33
1795323394 33
1795323399 33
1795323404 33
1795323409 33
1795323414 33
1795323419 33
1795323424 33
1795323429 33
1795323434 33
1795323439 66
1795323444 66
```
</details>

---

