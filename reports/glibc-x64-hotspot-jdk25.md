---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-22 12:02:56 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 30-32 cores)</summary>

```
1776873416 30
1776873421 30
1776873426 30
1776873431 30
1776873436 32
1776873441 32
1776873446 32
1776873451 32
1776873456 32
1776873461 32
1776873466 32
1776873471 32
1776873476 32
1776873481 32
1776873486 32
1776873491 32
1776873496 31
1776873501 31
1776873506 32
1776873511 32
```
</details>

---

