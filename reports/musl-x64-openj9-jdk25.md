---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:03:12 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (6 unique values: 45-79 cores)</summary>

```
1789743454 79
1789743459 79
1789743464 79
1789743469 79
1789743474 59
1789743479 59
1789743484 57
1789743489 57
1789743494 57
1789743499 57
1789743504 57
1789743509 57
1789743514 55
1789743519 55
1789743524 55
1789743529 55
1789743534 55
1789743539 45
1789743544 45
1789743549 45
```
</details>

---

