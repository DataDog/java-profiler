---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 09:21:52 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787059023 43
1787059028 43
1787059033 43
1787059038 43
1787059043 43
1787059048 43
1787059053 43
1787059058 43
1787059063 43
1787059068 48
1787059073 48
1787059079 48
1787059084 48
1787059089 48
1787059094 48
1787059099 48
1787059104 48
1787059109 48
1787059114 48
1787059119 48
```
</details>

---

