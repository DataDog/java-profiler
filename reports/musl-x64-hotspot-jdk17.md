---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 12:28:40 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 51-55 cores)</summary>

```
1792772628 51
1792772633 51
1792772638 51
1792772643 51
1792772648 53
1792772653 53
1792772658 53
1792772663 53
1792772668 53
1792772673 53
1792772678 53
1792772683 53
1792772688 53
1792772693 53
1792772698 53
1792772703 53
1792772708 53
1792772713 53
1792772718 53
1792772723 53
```
</details>

---

