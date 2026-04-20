---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 04:28:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 8 |
| Allocations | 421 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1776673411 27
1776673416 27
1776673421 27
1776673426 27
1776673431 27
1776673436 32
1776673441 32
1776673446 32
1776673451 32
1776673456 32
1776673461 32
1776673466 32
1776673471 32
1776673476 32
1776673481 32
1776673486 32
1776673491 32
1776673496 32
1776673501 32
1776673506 32
```
</details>

---

