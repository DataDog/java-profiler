---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 04:38:15 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1786523552 61
1786523557 61
1786523562 61
1786523567 61
1786523572 61
1786523577 59
1786523582 59
1786523587 59
1786523592 59
1786523597 59
1786523602 59
1786523607 59
1786523612 59
1786523617 59
1786523622 59
1786523627 59
1786523632 59
1786523637 59
1786523642 59
1786523647 59
```
</details>

---

