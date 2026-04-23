---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 18:00:38 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 9 |
| Allocations | 208 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776981431 59
1776981436 59
1776981441 59
1776981446 59
1776981451 59
1776981456 59
1776981461 59
1776981466 59
1776981471 59
1776981476 59
1776981481 64
1776981486 64
1776981491 64
1776981496 64
1776981501 64
1776981506 64
1776981511 64
1776981516 64
1776981521 64
1776981526 64
```
</details>

---

