---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-05 13:24:31 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 8 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791220774 30
1791220779 30
1791220784 30
1791220789 30
1791220794 30
1791220799 30
1791220804 30
1791220809 30
1791220814 30
1791220819 30
1791220824 30
1791220829 30
1791220834 30
1791220839 30
1791220844 32
1791220849 32
1791220854 32
1791220859 32
1791220864 32
1791220869 32
```
</details>

---

