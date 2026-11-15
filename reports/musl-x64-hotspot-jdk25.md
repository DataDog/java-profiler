---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-14 19:51:08 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (5 unique values: 41-75 cores)</summary>

```
1794703613 41
1794703618 74
1794703623 74
1794703628 74
1794703633 74
1794703638 53
1794703643 53
1794703648 53
1794703653 53
1794703658 53
1794703663 75
1794703668 75
1794703673 75
1794703678 75
1794703683 75
1794703688 75
1794703693 75
1794703698 75
1794703703 75
1794703708 75
```
</details>

---

