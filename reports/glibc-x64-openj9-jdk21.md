---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-29 06:14:25 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 15.70/sec |
| Health Score | 981% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 21.77/sec |
| Health Score | 1361% |
| Threads | 9 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 22-24 cores)</summary>

```
1769684920 24
1769684925 24
1769684930 24
1769684935 24
1769684940 24
1769684945 24
1769684950 22
1769684955 22
1769684960 22
1769684965 22
1769684970 22
1769684975 22
1769684980 22
1769684985 22
1769684990 24
1769684995 24
1769685000 24
1769685005 24
1769685010 24
1769685015 24
```
</details>

---

