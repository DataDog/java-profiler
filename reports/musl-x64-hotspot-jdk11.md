---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-29 07:38:32 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 9 |
| Allocations | 564 |

<details>
<summary>CPU Timeline (3 unique values: 45-70 cores)</summary>

```
1777462473 45
1777462478 45
1777462483 45
1777462488 45
1777462493 45
1777462498 45
1777462503 45
1777462508 45
1777462513 45
1777462518 45
1777462523 45
1777462528 45
1777462533 45
1777462538 45
1777462543 65
1777462548 65
1777462553 70
1777462558 70
1777462563 70
1777462568 70
```
</details>

---

