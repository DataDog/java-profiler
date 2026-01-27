---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-27 14:14:21 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 15.27/sec |
| Health Score | 954% |
| Threads | 8 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 21.03/sec |
| Health Score | 1314% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769540946 32
1769540951 32
1769540956 32
1769540961 32
1769540966 32
1769540971 32
1769540976 32
1769540981 32
1769540986 32
1769540991 32
1769540996 32
1769541001 32
1769541006 32
1769541011 32
1769541016 32
1769541021 32
1769541026 32
1769541031 32
1769541036 32
1769541041 32
```
</details>

---

