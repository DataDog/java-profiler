---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:54:33 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (5 unique values: 35-46 cores)</summary>

```
1791470950 36
1791470955 36
1791470960 41
1791470965 41
1791470970 46
1791470975 46
1791470980 40
1791470985 40
1791470990 40
1791470995 40
1791471000 40
1791471005 40
1791471010 35
1791471015 35
1791471020 35
1791471025 35
1791471030 35
1791471035 35
1791471040 35
1791471045 35
```
</details>

---

