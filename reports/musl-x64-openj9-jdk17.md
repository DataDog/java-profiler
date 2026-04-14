---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-14 14:58:18 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (7 unique values: 55-78 cores)</summary>

```
1776192782 61
1776192787 61
1776192792 63
1776192797 63
1776192802 63
1776192807 63
1776192812 63
1776192817 63
1776192822 59
1776192827 59
1776192833 59
1776192838 59
1776192843 59
1776192848 55
1776192853 55
1776192858 60
1776192863 60
1776192868 60
1776192873 60
1776192878 78
```
</details>

---

