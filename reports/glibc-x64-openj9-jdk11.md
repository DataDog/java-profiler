---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 11:23:37 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 815 |
| Sample Rate | 13.58/sec |
| Health Score | 849% |
| Threads | 10 |
| Allocations | 552 |

<details>
<summary>CPU Timeline (4 unique values: 83-89 cores)</summary>

```
1791299907 87
1791299912 87
1791299917 87
1791299922 87
1791299927 87
1791299932 87
1791299937 87
1791299942 87
1791299947 87
1791299952 87
1791299957 85
1791299962 85
1791299967 85
1791299973 85
1791299978 85
1791299983 85
1791299988 85
1791299993 83
1791299998 83
1791300003 83
```
</details>

---

