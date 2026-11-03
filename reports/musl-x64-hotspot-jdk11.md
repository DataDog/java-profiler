---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 21:59:32 EST

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
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 54-96 cores)</summary>

```
1793674429 96
1793674434 96
1793674439 96
1793674444 96
1793674449 96
1793674454 96
1793674459 96
1793674464 96
1793674469 96
1793674474 96
1793674479 96
1793674484 96
1793674489 96
1793674494 96
1793674499 96
1793674504 96
1793674509 96
1793674514 96
1793674519 96
1793674524 54
```
</details>

---

