---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-17 12:00:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776441369 59
1776441374 59
1776441379 59
1776441385 64
1776441390 64
1776441395 64
1776441400 64
1776441405 64
1776441410 64
1776441415 64
1776441420 64
1776441425 64
1776441430 64
1776441435 64
1776441440 64
1776441445 64
1776441450 64
1776441455 64
1776441460 64
1776441465 64
```
</details>

---

