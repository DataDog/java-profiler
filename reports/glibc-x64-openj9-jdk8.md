---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-05 05:52:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 46-91 cores)</summary>

```
1791193594 91
1791193599 91
1791193604 91
1791193610 91
1791193615 91
1791193620 91
1791193625 91
1791193630 91
1791193635 91
1791193640 91
1791193645 51
1791193650 51
1791193655 46
1791193660 46
1791193665 46
1791193670 46
1791193675 46
1791193680 46
1791193685 49
1791193690 49
```
</details>

---

