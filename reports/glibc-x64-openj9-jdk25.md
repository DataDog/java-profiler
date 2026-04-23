---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 10:22:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (6 unique values: 82-96 cores)</summary>

```
1776953708 84
1776953713 84
1776953718 84
1776953723 84
1776953728 84
1776953733 84
1776953738 84
1776953743 82
1776953748 82
1776953753 82
1776953758 82
1776953763 82
1776953768 86
1776953773 86
1776953778 86
1776953783 86
1776953788 86
1776953793 86
1776953798 86
1776953803 86
```
</details>

---

