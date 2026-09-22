---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 10:44:36 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 902 |
| Sample Rate | 15.03/sec |
| Health Score | 939% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1790087781 94
1790087786 94
1790087791 94
1790087796 94
1790087801 94
1790087806 96
1790087811 96
1790087816 96
1790087821 96
1790087826 96
1790087831 96
1790087836 96
1790087841 96
1790087846 96
1790087851 96
1790087856 96
1790087861 96
1790087866 96
1790087871 96
1790087876 96
```
</details>

---

