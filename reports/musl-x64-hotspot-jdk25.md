---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 08:17:30 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 46-52 cores)</summary>

```
1793362379 52
1793362384 52
1793362389 52
1793362394 52
1793362399 52
1793362404 52
1793362409 52
1793362414 52
1793362419 52
1793362424 52
1793362429 52
1793362434 52
1793362439 52
1793362444 46
1793362449 46
1793362454 46
1793362459 46
1793362464 46
1793362469 48
1793362474 48
```
</details>

---

