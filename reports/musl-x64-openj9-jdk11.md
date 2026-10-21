---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 08:20:55 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (4 unique values: 21-32 cores)</summary>

```
1792584842 21
1792584847 21
1792584852 21
1792584857 21
1792584862 21
1792584867 21
1792584872 21
1792584877 21
1792584882 30
1792584887 30
1792584892 30
1792584897 30
1792584902 30
1792584907 30
1792584912 32
1792584917 32
1792584922 32
1792584927 32
1792584932 29
1792584937 29
```
</details>

---

