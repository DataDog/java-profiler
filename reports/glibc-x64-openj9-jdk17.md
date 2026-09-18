---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:05:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1789743474 40
1789743479 40
1789743484 40
1789743489 40
1789743494 40
1789743499 40
1789743504 40
1789743509 40
1789743514 40
1789743519 40
1789743524 40
1789743529 48
1789743534 48
1789743539 48
1789743544 48
1789743549 48
1789743554 48
1789743559 48
1789743564 48
1789743569 48
```
</details>

---

