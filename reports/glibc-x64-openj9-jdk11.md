---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-16 12:11:36 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 864 |
| Sample Rate | 14.40/sec |
| Health Score | 900% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 51-60 cores)</summary>

```
1789574809 60
1789574814 60
1789574819 60
1789574824 60
1789574829 60
1789574834 60
1789574839 60
1789574844 60
1789574849 60
1789574854 51
1789574859 51
1789574864 51
1789574869 51
1789574874 51
1789574879 51
1789574884 51
1789574889 51
1789574894 51
1789574899 51
1789574904 51
```
</details>

---

