---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-24 04:38:23 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 364 |
| Sample Rate | 6.07/sec |
| Health Score | 379% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 10 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 60-62 cores)</summary>

```
1790238859 62
1790238864 61
1790238869 61
1790238874 61
1790238879 61
1790238884 61
1790238889 61
1790238894 61
1790238899 61
1790238904 61
1790238909 61
1790238914 60
1790238919 60
1790238924 60
1790238929 60
1790238934 60
1790238939 60
1790238944 60
1790238949 60
1790238954 60
```
</details>

---

