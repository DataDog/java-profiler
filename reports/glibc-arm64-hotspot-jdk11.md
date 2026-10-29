---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 13:49:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 23-36 cores)</summary>

```
1793295839 23
1793295844 23
1793295849 23
1793295854 23
1793295859 23
1793295864 23
1793295869 23
1793295874 23
1793295879 36
1793295884 36
1793295889 36
1793295894 36
1793295899 23
1793295904 23
1793295909 23
1793295914 23
1793295919 23
1793295924 23
1793295929 23
1793295934 23
```
</details>

---

