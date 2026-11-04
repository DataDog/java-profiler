---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 08:41:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 16 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1793799441 51
1793799446 51
1793799451 51
1793799456 51
1793799461 51
1793799466 51
1793799471 51
1793799476 51
1793799481 51
1793799486 51
1793799491 46
1793799496 46
1793799501 46
1793799506 46
1793799511 46
1793799516 46
1793799521 46
1793799526 46
1793799531 41
1793799536 41
```
</details>

---

