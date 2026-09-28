---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 10:16:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1790604658 32
1790604663 32
1790604668 32
1790604673 32
1790604678 32
1790604683 32
1790604688 32
1790604693 32
1790604698 32
1790604703 32
1790604708 30
1790604713 30
1790604718 30
1790604723 30
1790604728 28
1790604733 28
1790604738 28
1790604743 28
1790604748 28
1790604753 28
```
</details>

---

