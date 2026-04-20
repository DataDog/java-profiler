---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 05:36:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 10 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 356 |
| Sample Rate | 5.93/sec |
| Health Score | 371% |
| Threads | 13 |
| Allocations | 161 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776677406 64
1776677411 64
1776677416 64
1776677421 64
1776677426 64
1776677431 64
1776677436 64
1776677441 64
1776677446 64
1776677451 64
1776677456 64
1776677461 64
1776677466 64
1776677471 64
1776677476 64
1776677481 64
1776677486 64
1776677491 64
1776677496 59
1776677501 59
```
</details>

---

