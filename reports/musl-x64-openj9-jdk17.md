---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-22 12:02:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1776873421 30
1776873426 30
1776873431 30
1776873436 30
1776873441 30
1776873446 30
1776873451 30
1776873456 30
1776873461 30
1776873466 30
1776873471 30
1776873476 32
1776873481 32
1776873486 32
1776873491 32
1776873496 32
1776873501 32
1776873506 32
1776873511 32
1776873516 32
```
</details>

---

