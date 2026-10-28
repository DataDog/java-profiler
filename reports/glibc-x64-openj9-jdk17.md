---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:48:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1793187922 71
1793187927 71
1793187932 71
1793187937 71
1793187942 71
1793187947 71
1793187953 71
1793187958 71
1793187963 71
1793187968 71
1793187973 71
1793187978 71
1793187983 71
1793187988 71
1793187993 71
1793187998 71
1793188003 73
1793188008 73
1793188013 73
1793188018 73
```
</details>

---

