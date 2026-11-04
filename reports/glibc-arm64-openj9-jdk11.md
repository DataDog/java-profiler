---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 08:41:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 8 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1793799400 48
1793799405 48
1793799410 48
1793799415 48
1793799420 48
1793799425 48
1793799430 48
1793799435 48
1793799440 48
1793799445 48
1793799450 48
1793799455 48
1793799460 48
1793799465 48
1793799470 48
1793799475 48
1793799480 48
1793799485 48
1793799490 48
1793799495 48
```
</details>

---

