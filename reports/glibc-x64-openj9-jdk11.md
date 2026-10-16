---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 04:44:28 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1792139952 53
1792139957 55
1792139962 55
1792139967 55
1792139972 55
1792139977 55
1792139982 55
1792139987 53
1792139992 53
1792139997 53
1792140002 53
1792140007 53
1792140012 53
1792140017 55
1792140022 55
1792140027 55
1792140032 55
1792140037 55
1792140042 55
1792140047 55
```
</details>

---

