---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 06:43:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 10 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 11 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (3 unique values: 78-86 cores)</summary>

```
1778150297 78
1778150302 78
1778150307 78
1778150312 78
1778150317 78
1778150322 78
1778150327 82
1778150332 82
1778150337 86
1778150342 86
1778150347 86
1778150352 86
1778150357 86
1778150362 86
1778150367 86
1778150372 86
1778150377 86
1778150382 86
1778150387 86
1778150392 86
```
</details>

---

