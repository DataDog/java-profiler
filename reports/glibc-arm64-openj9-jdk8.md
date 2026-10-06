---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-06 12:01:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1791301952 46
1791301957 42
1791301962 42
1791301967 42
1791301972 42
1791301977 42
1791301982 42
1791301987 43
1791301992 43
1791301997 43
1791302002 43
1791302007 48
1791302012 48
1791302017 48
1791302022 48
1791302027 48
1791302032 48
1791302037 48
1791302042 48
1791302047 48
```
</details>

---

