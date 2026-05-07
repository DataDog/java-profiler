---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 09:00:16 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 53-90 cores)</summary>

```
1778158366 53
1778158371 53
1778158376 53
1778158381 59
1778158386 59
1778158391 59
1778158396 59
1778158401 59
1778158406 59
1778158411 59
1778158416 57
1778158421 57
1778158426 57
1778158431 57
1778158436 57
1778158441 57
1778158446 90
1778158451 90
1778158456 90
1778158461 90
```
</details>

---

