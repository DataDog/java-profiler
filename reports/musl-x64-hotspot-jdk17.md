---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-29 07:38:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (5 unique values: 43-72 cores)</summary>

```
1777462468 43
1777462473 43
1777462478 43
1777462483 45
1777462488 45
1777462493 52
1777462498 52
1777462503 52
1777462508 52
1777462513 52
1777462518 52
1777462523 52
1777462528 48
1777462533 48
1777462538 48
1777462543 48
1777462548 72
1777462553 72
1777462558 72
1777462563 72
```
</details>

---

