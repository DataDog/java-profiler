---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 03:05:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 12 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1790665328 96
1790665333 96
1790665338 96
1790665343 96
1790665348 96
1790665353 96
1790665358 96
1790665363 96
1790665368 96
1790665373 96
1790665378 94
1790665383 94
1790665388 94
1790665393 94
1790665398 94
1790665403 94
1790665408 94
1790665413 94
1790665418 94
1790665423 94
```
</details>

---

