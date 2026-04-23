---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 04:32:56 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (5 unique values: 75-84 cores)</summary>

```
1776932897 76
1776932902 76
1776932907 76
1776932912 78
1776932917 78
1776932922 78
1776932927 78
1776932932 78
1776932937 78
1776932942 75
1776932947 75
1776932952 75
1776932957 75
1776932962 75
1776932967 75
1776932972 75
1776932977 75
1776932982 75
1776932987 80
1776932992 80
```
</details>

---

