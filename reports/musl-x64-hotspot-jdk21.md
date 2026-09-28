---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 10:16:38 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 42-75 cores)</summary>

```
1790604638 75
1790604643 75
1790604648 75
1790604653 75
1790604658 75
1790604663 75
1790604668 75
1790604673 75
1790604678 75
1790604683 75
1790604688 75
1790604693 42
1790604698 42
1790604703 42
1790604708 42
1790604713 42
1790604718 42
1790604723 42
1790604728 42
1790604733 42
```
</details>

---

