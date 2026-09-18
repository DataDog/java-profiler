---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:07:48 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1043 |
| Sample Rate | 17.38/sec |
| Health Score | 1086% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 80-84 cores)</summary>

```
1789743514 80
1789743519 80
1789743524 80
1789743529 80
1789743534 82
1789743539 82
1789743544 82
1789743549 82
1789743554 82
1789743559 84
1789743564 84
1789743569 84
1789743574 84
1789743579 82
1789743584 82
1789743589 82
1789743594 82
1789743599 82
1789743604 82
1789743609 82
```
</details>

---

