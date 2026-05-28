---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-28 11:27:30 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 56-73 cores)</summary>

```
1779981604 71
1779981609 71
1779981614 71
1779981619 71
1779981624 71
1779981629 71
1779981634 71
1779981639 73
1779981644 73
1779981649 73
1779981654 73
1779981659 73
1779981664 73
1779981669 73
1779981674 73
1779981679 73
1779981684 73
1779981689 56
1779981694 56
1779981699 56
```
</details>

---

