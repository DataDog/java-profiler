---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-23 04:32:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 48-56 cores)</summary>

```
1776932908 48
1776932913 48
1776932918 50
1776932923 50
1776932928 50
1776932933 50
1776932938 50
1776932943 50
1776932948 56
1776932953 56
1776932958 56
1776932963 56
1776932968 56
1776932973 56
1776932978 56
1776932983 56
1776932988 56
1776932993 56
1776932998 56
1776933003 56
```
</details>

---

