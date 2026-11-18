---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 08:22:46 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 60-81 cores)</summary>

```
1795007937 81
1795007942 81
1795007947 81
1795007952 81
1795007957 81
1795007962 81
1795007967 60
1795007972 60
1795007977 60
1795007982 60
1795007987 60
1795007992 60
1795007997 60
1795008002 60
1795008007 60
1795008012 60
1795008017 60
1795008022 60
1795008027 60
1795008032 60
```
</details>

---

