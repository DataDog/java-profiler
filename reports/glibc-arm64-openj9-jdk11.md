---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 01:04:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793249959 36
1793249964 36
1793249969 36
1793249974 36
1793249979 36
1793249984 36
1793249989 36
1793249994 36
1793249999 36
1793250004 36
1793250009 36
1793250014 36
1793250019 36
1793250024 36
1793250029 36
1793250034 36
1793250039 36
1793250044 36
1793250049 36
1793250054 36
```
</details>

---

