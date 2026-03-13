---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-13 05:26:05 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (5 unique values: 51-61 cores)</summary>

```
1773393640 52
1773393645 53
1773393650 53
1773393655 51
1773393660 51
1773393665 51
1773393670 51
1773393675 57
1773393680 57
1773393685 57
1773393690 57
1773393695 57
1773393700 61
1773393705 61
1773393710 61
1773393715 61
1773393720 61
1773393725 61
1773393730 61
1773393735 61
```
</details>

---

