---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-14 04:32:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 428 |
| Sample Rate | 7.13/sec |
| Health Score | 446% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1791966428 76
1791966433 76
1791966438 76
1791966443 76
1791966448 76
1791966453 76
1791966458 76
1791966463 76
1791966468 76
1791966473 76
1791966478 76
1791966483 76
1791966488 76
1791966493 76
1791966498 76
1791966503 76
1791966508 74
1791966513 74
1791966518 74
1791966523 74
```
</details>

---

