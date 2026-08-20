---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 10:05:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (5 unique values: 36-76 cores)</summary>

```
1787234375 74
1787234380 76
1787234386 76
1787234391 76
1787234396 76
1787234401 76
1787234406 76
1787234411 76
1787234416 76
1787234421 76
1787234426 76
1787234431 76
1787234436 76
1787234441 76
1787234446 76
1787234451 68
1787234456 68
1787234461 68
1787234466 56
1787234471 56
```
</details>

---

