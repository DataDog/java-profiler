---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 03:59:20 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 34-52 cores)</summary>

```
1791532506 34
1791532511 52
1791532516 52
1791532521 50
1791532526 50
1791532531 50
1791532536 50
1791532541 50
1791532546 50
1791532551 50
1791532556 50
1791532561 50
1791532566 50
1791532571 50
1791532576 50
1791532581 50
1791532586 50
1791532591 50
1791532596 50
1791532601 50
```
</details>

---

