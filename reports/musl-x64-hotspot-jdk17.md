---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 10:36:06 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (4 unique values: 71-76 cores)</summary>

```
1793370627 76
1793370632 76
1793370637 76
1793370642 73
1793370647 73
1793370652 73
1793370657 71
1793370662 71
1793370667 71
1793370672 71
1793370677 73
1793370682 73
1793370687 73
1793370692 73
1793370697 73
1793370702 75
1793370707 75
1793370712 75
1793370717 75
1793370722 75
```
</details>

---

