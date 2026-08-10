---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 05:48:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1786354986 28
1786354991 28
1786354996 28
1786355001 28
1786355006 28
1786355011 28
1786355016 28
1786355021 28
1786355026 30
1786355031 30
1786355036 30
1786355041 30
1786355046 30
1786355051 30
1786355056 30
1786355061 30
1786355066 32
1786355071 32
1786355076 32
1786355081 32
```
</details>

---

