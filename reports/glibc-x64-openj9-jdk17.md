---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 04:44:28 EDT

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
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 55-76 cores)</summary>

```
1792139977 55
1792139982 55
1792139987 55
1792139992 55
1792139997 55
1792140002 55
1792140007 55
1792140012 55
1792140017 55
1792140022 55
1792140027 55
1792140032 55
1792140037 55
1792140042 55
1792140047 55
1792140052 76
1792140057 76
1792140062 76
1792140067 59
1792140072 59
```
</details>

---

