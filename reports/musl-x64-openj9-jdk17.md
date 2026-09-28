---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 14:12:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 22-28 cores)</summary>

```
1790618881 22
1790618886 22
1790618891 22
1790618896 22
1790618901 22
1790618906 22
1790618911 24
1790618916 24
1790618921 24
1790618926 24
1790618931 24
1790618936 24
1790618941 28
1790618946 28
1790618951 28
1790618956 28
1790618961 28
1790618966 28
1790618971 28
1790618976 28
```
</details>

---

