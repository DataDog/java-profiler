---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:43:00 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 12-48 cores)</summary>

```
1778582317 12
1778582322 12
1778582327 12
1778582332 12
1778582337 12
1778582342 12
1778582347 12
1778582352 12
1778582357 48
1778582362 48
1778582367 39
1778582372 39
1778582377 39
1778582382 39
1778582387 39
1778582392 39
1778582397 39
1778582402 39
1778582407 39
1778582412 39
```
</details>

---

