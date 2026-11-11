---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 05:29:42 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1794392625 92
1794392630 92
1794392635 92
1794392640 92
1794392645 92
1794392650 92
1794392655 92
1794392660 92
1794392665 92
1794392670 92
1794392675 92
1794392680 94
1794392685 94
1794392690 96
1794392695 96
1794392700 96
1794392705 96
1794392710 96
1794392715 96
1794392720 96
```
</details>

---

