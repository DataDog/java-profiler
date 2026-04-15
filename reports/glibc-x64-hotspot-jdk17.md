---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-15 12:49:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 92-96 cores)</summary>

```
1776271518 92
1776271523 92
1776271528 96
1776271533 96
1776271538 96
1776271543 96
1776271548 96
1776271553 96
1776271558 96
1776271563 96
1776271568 96
1776271573 96
1776271578 96
1776271583 96
1776271588 96
1776271593 96
1776271598 96
1776271603 96
1776271608 96
1776271613 96
```
</details>

---

