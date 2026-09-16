---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-16 12:13:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 9 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 76-81 cores)</summary>

```
1789574789 76
1789574794 76
1789574799 76
1789574804 76
1789574809 76
1789574814 76
1789574819 76
1789574824 76
1789574829 76
1789574834 76
1789574839 76
1789574844 81
1789574849 81
1789574854 81
1789574859 81
1789574864 81
1789574869 81
1789574874 81
1789574879 81
1789574884 81
```
</details>

---

