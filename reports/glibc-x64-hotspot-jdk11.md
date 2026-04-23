---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 04:28:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (5 unique values: 38-47 cores)</summary>

```
1776932552 40
1776932557 38
1776932562 38
1776932567 42
1776932572 42
1776932577 42
1776932582 42
1776932587 42
1776932592 42
1776932597 44
1776932602 44
1776932607 44
1776932612 44
1776932617 44
1776932622 47
1776932627 47
1776932632 47
1776932637 47
1776932642 44
1776932647 44
```
</details>

---

