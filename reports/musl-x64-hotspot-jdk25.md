---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-07 13:11:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 50-60 cores)</summary>

```
1786122391 60
1786122396 60
1786122401 60
1786122406 58
1786122411 58
1786122416 58
1786122421 58
1786122426 58
1786122431 58
1786122436 58
1786122441 58
1786122446 58
1786122451 58
1786122456 58
1786122461 58
1786122466 58
1786122471 58
1786122476 58
1786122481 58
1786122486 58
```
</details>

---

