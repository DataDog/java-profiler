---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-04 09:03:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 9 |
| Allocations | 562 |

<details>
<summary>CPU Timeline (4 unique values: 58-70 cores)</summary>

```
1770213470 70
1770213475 70
1770213480 70
1770213485 66
1770213490 66
1770213495 66
1770213500 66
1770213505 66
1770213510 66
1770213515 66
1770213520 66
1770213525 58
1770213530 58
1770213535 58
1770213540 58
1770213545 58
1770213550 60
1770213555 60
1770213560 60
1770213565 60
```
</details>

---

