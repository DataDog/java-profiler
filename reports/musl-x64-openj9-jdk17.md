---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 06:49:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 56-76 cores)</summary>

```
1792579470 76
1792579475 76
1792579480 74
1792579485 74
1792579490 74
1792579495 74
1792579500 74
1792579505 74
1792579510 76
1792579515 76
1792579520 56
1792579525 56
1792579530 56
1792579535 56
1792579540 56
1792579545 56
1792579550 56
1792579555 61
1792579560 61
1792579565 63
```
</details>

---

