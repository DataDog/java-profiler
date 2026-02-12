---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-12 06:37:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1770895942 32
1770895947 32
1770895952 32
1770895957 32
1770895962 32
1770895967 32
1770895972 32
1770895977 32
1770895982 32
1770895987 32
1770895992 32
1770895997 32
1770896002 32
1770896007 32
1770896012 32
1770896017 32
1770896022 32
1770896027 32
1770896032 32
1770896037 32
```
</details>

---

