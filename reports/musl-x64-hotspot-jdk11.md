---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 07:00:18 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 9 |
| Allocations | 585 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1793098437 96
1793098442 96
1793098447 96
1793098452 96
1793098457 96
1793098462 96
1793098467 96
1793098472 96
1793098477 96
1793098482 96
1793098487 96
1793098492 96
1793098497 96
1793098502 96
1793098507 96
1793098512 96
1793098517 96
1793098522 96
1793098527 94
1793098532 94
```
</details>

---

