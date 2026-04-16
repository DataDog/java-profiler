---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-16 12:58:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 9 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1776358412 57
1776358417 57
1776358422 57
1776358427 57
1776358432 57
1776358437 57
1776358442 57
1776358447 57
1776358452 57
1776358457 57
1776358462 57
1776358468 57
1776358473 57
1776358478 57
1776358483 57
1776358488 57
1776358493 57
1776358498 59
1776358503 59
1776358508 59
```
</details>

---

