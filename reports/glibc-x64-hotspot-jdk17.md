---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-06 04:52:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 417 |

<details>
<summary>CPU Timeline (4 unique values: 21-27 cores)</summary>

```
1772790376 21
1772790381 21
1772790386 21
1772790391 21
1772790396 21
1772790401 21
1772790406 21
1772790411 21
1772790416 21
1772790421 21
1772790426 25
1772790431 25
1772790436 27
1772790441 27
1772790446 27
1772790451 27
1772790456 27
1772790461 27
1772790466 27
1772790471 27
```
</details>

---

