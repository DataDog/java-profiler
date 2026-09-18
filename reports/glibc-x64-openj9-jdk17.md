---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:15:14 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 10 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (2 unique values: 43-73 cores)</summary>

```
1789743660 43
1789743665 43
1789743670 43
1789743675 43
1789743680 43
1789743685 43
1789743690 73
1789743695 73
1789743700 73
1789743705 73
1789743710 73
1789743715 73
1789743720 73
1789743725 73
1789743730 73
1789743735 73
1789743740 73
1789743745 73
1789743750 73
1789743755 73
```
</details>

---

