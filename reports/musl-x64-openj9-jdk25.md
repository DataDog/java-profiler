---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 13:02:42 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 12 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 47-53 cores)</summary>

```
1790787381 47
1790787386 47
1790787391 53
1790787396 53
1790787402 53
1790787407 53
1790787412 50
1790787417 50
1790787422 50
1790787427 50
1790787432 50
1790787437 50
1790787442 50
1790787447 48
1790787452 48
1790787457 48
1790787462 48
1790787467 48
1790787472 48
1790787477 50
```
</details>

---

