---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-29 07:38:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1777462463 30
1777462468 30
1777462473 30
1777462478 30
1777462483 30
1777462488 30
1777462493 30
1777462498 30
1777462503 30
1777462508 30
1777462513 30
1777462518 30
1777462523 30
1777462528 30
1777462533 30
1777462538 32
1777462543 32
1777462548 32
1777462553 32
1777462558 32
```
</details>

---

