---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 10:29:00 EST

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
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1793978607 30
1793978612 32
1793978617 32
1793978622 32
1793978627 32
1793978632 29
1793978637 29
1793978642 29
1793978647 29
1793978652 29
1793978657 29
1793978662 29
1793978667 29
1793978672 29
1793978677 29
1793978682 29
1793978687 29
1793978692 29
1793978697 29
1793978702 29
```
</details>

---

