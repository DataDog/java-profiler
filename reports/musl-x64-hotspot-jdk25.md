---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-23 13:43:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (5 unique values: 84-90 cores)</summary>

```
1776965923 86
1776965928 86
1776965933 84
1776965938 84
1776965943 84
1776965948 87
1776965953 87
1776965958 87
1776965963 87
1776965968 87
1776965973 87
1776965978 87
1776965983 88
1776965988 88
1776965993 88
1776965998 90
1776966003 90
1776966008 90
1776966013 90
1776966018 90
```
</details>

---

