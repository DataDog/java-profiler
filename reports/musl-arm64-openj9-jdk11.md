---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-26 16:34:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 9 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1777235397 32
1777235402 32
1777235407 32
1777235412 32
1777235417 32
1777235422 32
1777235427 32
1777235432 32
1777235437 32
1777235442 32
1777235447 32
1777235452 32
1777235457 32
1777235463 32
1777235468 32
1777235473 32
1777235478 32
1777235483 32
1777235488 32
1777235493 32
```
</details>

---

