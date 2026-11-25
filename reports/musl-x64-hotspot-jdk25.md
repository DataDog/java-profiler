---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:03:53 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 66-72 cores)</summary>

```
1795618470 66
1795618475 66
1795618480 66
1795618486 66
1795618491 66
1795618496 66
1795618501 66
1795618506 66
1795618511 66
1795618516 66
1795618521 66
1795618526 66
1795618531 66
1795618536 68
1795618541 68
1795618546 68
1795618551 68
1795618556 70
1795618561 70
1795618566 70
```
</details>

---

