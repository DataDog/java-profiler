---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 10:34:20 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1016 |
| Sample Rate | 16.93/sec |
| Health Score | 1058% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 18-28 cores)</summary>

```
1776695065 18
1776695070 18
1776695075 18
1776695080 23
1776695085 23
1776695090 23
1776695095 23
1776695100 23
1776695105 23
1776695110 23
1776695115 23
1776695120 23
1776695125 23
1776695130 23
1776695135 23
1776695140 23
1776695145 23
1776695150 28
1776695155 28
1776695160 28
```
</details>

---

