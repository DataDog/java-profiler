---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 11:41:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1776699050 32
1776699055 32
1776699060 32
1776699065 32
1776699070 32
1776699075 32
1776699080 30
1776699085 30
1776699090 28
1776699095 28
1776699100 30
1776699105 30
1776699110 30
1776699115 30
1776699120 30
1776699125 30
1776699130 30
1776699135 30
1776699140 30
1776699145 30
```
</details>

---

