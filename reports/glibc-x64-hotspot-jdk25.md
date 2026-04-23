---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-23 04:28:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1776932427 20
1776932432 20
1776932437 20
1776932442 20
1776932447 20
1776932452 20
1776932457 20
1776932462 20
1776932467 22
1776932472 22
1776932477 22
1776932482 22
1776932487 22
1776932492 22
1776932497 22
1776932502 22
1776932507 22
1776932512 22
1776932517 22
1776932522 22
```
</details>

---

