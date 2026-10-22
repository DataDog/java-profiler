---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 04:49:18 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 74-96 cores)</summary>

```
1792658610 76
1792658615 76
1792658620 76
1792658625 76
1792658630 76
1792658635 76
1792658640 76
1792658645 96
1792658650 96
1792658655 76
1792658660 76
1792658665 76
1792658670 76
1792658675 76
1792658680 76
1792658685 76
1792658690 76
1792658695 76
1792658700 76
1792658705 76
```
</details>

---

