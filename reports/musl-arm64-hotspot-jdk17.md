---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 03:59:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 14 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1791532521 51
1791532526 51
1791532531 51
1791532536 51
1791532541 51
1791532546 51
1791532551 51
1791532556 51
1791532561 51
1791532566 51
1791532571 51
1791532576 51
1791532581 51
1791532586 51
1791532591 51
1791532596 51
1791532601 51
1791532606 51
1791532611 51
1791532616 64
```
</details>

---

