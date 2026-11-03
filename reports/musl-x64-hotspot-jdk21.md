---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 07:41:16 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 10 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1793709442 42
1793709447 42
1793709452 42
1793709457 42
1793709462 42
1793709468 42
1793709473 42
1793709478 40
1793709483 40
1793709488 40
1793709493 40
1793709498 40
1793709503 40
1793709508 40
1793709513 40
1793709518 40
1793709523 40
1793709528 40
1793709533 40
1793709538 40
```
</details>

---

