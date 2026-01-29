---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 06:14:25 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 18.93/sec |
| Health Score | 1183% |
| Threads | 8 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 25.67/sec |
| Health Score | 1604% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 71-77 cores)</summary>

```
1769684932 77
1769684937 77
1769684942 77
1769684947 77
1769684952 76
1769684957 76
1769684962 76
1769684967 77
1769684972 77
1769684977 77
1769684982 77
1769684987 77
1769684992 77
1769684997 75
1769685002 75
1769685007 77
1769685012 77
1769685017 77
1769685022 77
1769685027 77
```
</details>

---

