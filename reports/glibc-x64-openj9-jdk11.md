---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 11:15:14 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1042 |
| Sample Rate | 17.37/sec |
| Health Score | 1086% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 43-73 cores)</summary>

```
1789743654 43
1789743659 43
1789743664 43
1789743669 43
1789743674 43
1789743679 43
1789743684 43
1789743689 73
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
```
</details>

---

