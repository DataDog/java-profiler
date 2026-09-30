---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 10:20:50 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 10 |
| Allocations | 418 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1790777683 55
1790777688 55
1790777693 55
1790777698 55
1790777703 57
1790777708 57
1790777713 57
1790777718 57
1790777723 57
1790777728 57
1790777733 57
1790777738 57
1790777743 57
1790777748 57
1790777753 57
1790777758 57
1790777763 57
1790777768 57
1790777773 57
1790777778 57
```
</details>

---

