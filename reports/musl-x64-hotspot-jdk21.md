---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:01:15 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 11 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1793184652 64
1793184657 64
1793184662 66
1793184667 66
1793184672 66
1793184677 66
1793184682 66
1793184687 66
1793184692 66
1793184697 66
1793184702 66
1793184707 66
1793184712 66
1793184717 66
1793184722 66
1793184727 66
1793184732 66
1793184737 66
1793184742 66
1793184747 66
```
</details>

---

