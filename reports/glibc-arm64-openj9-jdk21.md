---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-01-29 06:14:25 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 10 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769684927 24
1769684932 24
1769684937 24
1769684942 24
1769684947 24
1769684952 24
1769684957 24
1769684962 24
1769684967 24
1769684972 24
1769684977 24
1769684982 24
1769684987 24
1769684992 24
1769684997 24
1769685002 24
1769685007 24
1769685012 24
1769685017 24
1769685022 24
```
</details>

---

