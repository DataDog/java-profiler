---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ❌ FAIL

**Date:** 2026-10-16 05:16:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 39-70 cores)</summary>

```
1792141892 70
1792141897 70
1792141902 70
1792141907 70
1792141912 70
1792141917 70
1792141922 70
1792141927 70
1792141932 39
1792141937 39
1792141942 39
1792141947 39
1792141952 39
1792141957 39
1792141962 39
1792141967 39
1792141972 62
1792141977 62
1792141982 62
1792141987 62
```
</details>

---

