---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-29 06:14:25 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 19.63/sec |
| Health Score | 1227% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769684931 32
1769684936 32
1769684941 32
1769684946 32
1769684951 32
1769684956 32
1769684961 32
1769684966 32
1769684971 32
1769684976 32
1769684981 32
1769684986 32
1769684991 32
1769684996 32
1769685001 32
1769685006 32
1769685011 32
1769685016 32
1769685021 30
1769685026 30
```
</details>

---

