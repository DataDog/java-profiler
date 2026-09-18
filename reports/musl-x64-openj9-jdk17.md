---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:03:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1131 |
| Sample Rate | 18.85/sec |
| Health Score | 1178% |
| Threads | 11 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (5 unique values: 68-80 cores)</summary>

```
1789743504 73
1789743509 73
1789743514 73
1789743519 79
1789743524 79
1789743529 79
1789743534 79
1789743539 79
1789743544 79
1789743549 80
1789743554 80
1789743559 80
1789743564 80
1789743569 80
1789743574 70
1789743579 70
1789743584 68
1789743589 68
1789743594 68
1789743600 68
```
</details>

---

