---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 06:23:10 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 75-84 cores)</summary>

```
1795605454 82
1795605459 82
1795605464 82
1795605469 82
1795605474 84
1795605479 84
1795605484 84
1795605489 84
1795605494 84
1795605499 84
1795605504 84
1795605509 84
1795605514 84
1795605519 84
1795605524 84
1795605529 84
1795605534 84
1795605539 84
1795605544 84
1795605549 84
```
</details>

---

