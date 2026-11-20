---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:21:10 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1029 |
| Sample Rate | 17.15/sec |
| Health Score | 1072% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795195048 64
1795195053 64
1795195058 64
1795195063 64
1795195068 64
1795195073 64
1795195078 64
1795195083 64
1795195088 64
1795195093 64
1795195098 64
1795195103 64
1795195108 64
1795195113 64
1795195118 64
1795195123 64
1795195128 64
1795195133 64
1795195139 64
1795195144 64
```
</details>

---

