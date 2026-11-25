---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795605033 29
1795605038 29
1795605043 29
1795605048 29
1795605053 29
1795605058 29
1795605063 29
1795605068 29
1795605073 29
1795605078 29
1795605083 29
1795605088 29
1795605093 34
1795605098 34
1795605103 34
1795605108 34
1795605113 34
1795605118 34
1795605123 34
1795605128 34
```
</details>

---

