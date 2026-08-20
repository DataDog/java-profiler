---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 10:05:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1085 |
| Sample Rate | 18.08/sec |
| Health Score | 1130% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1787234366 76
1787234371 76
1787234376 76
1787234381 76
1787234386 76
1787234391 76
1787234396 76
1787234401 76
1787234406 76
1787234411 76
1787234416 76
1787234421 76
1787234426 96
1787234431 96
1787234436 96
1787234441 96
1787234446 96
1787234451 96
1787234456 96
1787234461 96
```
</details>

---

