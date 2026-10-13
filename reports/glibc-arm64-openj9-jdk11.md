---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-13 08:37:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 356 |
| Sample Rate | 5.93/sec |
| Health Score | 371% |
| Threads | 13 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1791894830 48
1791894835 48
1791894840 48
1791894845 48
1791894850 48
1791894855 48
1791894860 48
1791894865 48
1791894870 48
1791894875 28
1791894880 28
1791894885 28
1791894890 28
1791894895 28
1791894901 28
1791894906 28
1791894911 28
1791894916 28
1791894921 28
1791894926 28
```
</details>

---

