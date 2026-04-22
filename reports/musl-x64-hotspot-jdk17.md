---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-22 14:08:56 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (5 unique values: 21-25 cores)</summary>

```
1776881020 23
1776881025 23
1776881030 23
1776881035 23
1776881040 25
1776881045 25
1776881050 25
1776881055 21
1776881060 21
1776881065 21
1776881070 21
1776881075 21
1776881080 21
1776881085 24
1776881090 24
1776881095 22
1776881100 22
1776881105 24
1776881110 24
1776881115 24
```
</details>

---

