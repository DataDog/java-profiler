---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 04:33:09 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 10 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 806 |
| Sample Rate | 13.43/sec |
| Health Score | 839% |
| Threads | 12 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 81-85 cores)</summary>

```
1773217597 85
1773217602 85
1773217607 85
1773217612 85
1773217617 85
1773217622 85
1773217627 85
1773217632 82
1773217637 82
1773217642 82
1773217647 82
1773217652 82
1773217657 82
1773217662 82
1773217667 83
1773217672 83
1773217677 83
1773217682 85
1773217687 85
1773217692 85
```
</details>

---

