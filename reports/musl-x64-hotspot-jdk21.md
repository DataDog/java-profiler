---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-14 04:32:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 809 |
| Sample Rate | 13.48/sec |
| Health Score | 842% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 18-25 cores)</summary>

```
1791966433 25
1791966438 25
1791966443 25
1791966448 25
1791966453 25
1791966458 25
1791966463 25
1791966468 25
1791966473 25
1791966478 25
1791966483 25
1791966488 25
1791966493 25
1791966498 25
1791966503 25
1791966508 25
1791966513 25
1791966518 20
1791966523 20
1791966528 18
```
</details>

---

