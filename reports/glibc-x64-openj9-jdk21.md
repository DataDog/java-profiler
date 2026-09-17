---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 13:52:02 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 10 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (2 unique values: 33-34 cores)</summary>

```
1789667296 34
1789667301 34
1789667306 34
1789667311 34
1789667316 34
1789667321 34
1789667326 34
1789667331 34
1789667336 34
1789667341 34
1789667346 34
1789667351 34
1789667356 34
1789667361 34
1789667366 34
1789667371 34
1789667376 34
1789667381 34
1789667386 33
1789667391 33
```
</details>

---

