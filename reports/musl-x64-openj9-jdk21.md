---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 07:21:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 46-56 cores)</summary>

```
1789989435 48
1789989440 48
1789989445 48
1789989450 48
1789989455 48
1789989460 48
1789989465 48
1789989470 48
1789989475 56
1789989480 56
1789989485 56
1789989490 56
1789989495 56
1789989500 56
1789989505 56
1789989510 56
1789989515 56
1789989520 56
1789989525 56
1789989530 56
```
</details>

---

