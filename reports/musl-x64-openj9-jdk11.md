---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 13:55:57 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 73-76 cores)</summary>

```
1776966675 76
1776966680 76
1776966685 76
1776966690 76
1776966695 73
1776966700 73
1776966705 73
1776966710 73
1776966715 75
1776966720 75
1776966725 76
1776966730 76
1776966735 76
1776966740 76
1776966745 76
1776966750 76
1776966755 76
1776966760 74
1776966765 74
1776966770 74
```
</details>

---

