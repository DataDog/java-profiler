---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 13:49:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 41-52 cores)</summary>

```
1793295911 41
1793295916 41
1793295921 41
1793295926 41
1793295931 41
1793295936 41
1793295941 41
1793295946 41
1793295951 41
1793295956 41
1793295961 41
1793295966 41
1793295971 41
1793295976 41
1793295981 41
1793295986 41
1793295991 41
1793295996 41
1793296001 41
1793296006 41
```
</details>

---

