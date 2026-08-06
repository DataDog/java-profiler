---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-06 09:49:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 11 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786023876 48
1786023881 48
1786023886 48
1786023891 48
1786023896 48
1786023901 48
1786023906 48
1786023911 48
1786023917 48
1786023922 48
1786023927 48
1786023932 43
1786023937 43
1786023942 43
1786023947 43
1786023952 43
1786023957 43
1786023962 43
1786023967 43
1786023972 43
```
</details>

---

