---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:07:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 65-96 cores)</summary>

```
1789743504 65
1789743509 65
1789743514 65
1789743519 65
1789743524 65
1789743529 65
1789743534 65
1789743539 65
1789743544 65
1789743549 96
1789743554 96
1789743559 96
1789743564 96
1789743569 96
1789743574 96
1789743579 96
1789743584 96
1789743589 96
1789743594 96
1789743599 96
```
</details>

---

