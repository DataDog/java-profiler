---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 14:35:35 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 78-83 cores)</summary>

```
1793125845 80
1793125850 80
1793125855 80
1793125860 80
1793125865 80
1793125870 80
1793125875 82
1793125880 82
1793125885 82
1793125890 82
1793125895 82
1793125900 82
1793125905 82
1793125910 82
1793125915 82
1793125920 80
1793125925 80
1793125930 80
1793125935 80
1793125940 83
```
</details>

---

