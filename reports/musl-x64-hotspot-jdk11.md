---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 06:41:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (4 unique values: 74-91 cores)</summary>

```
1794310614 75
1794310619 75
1794310624 75
1794310629 75
1794310634 75
1794310639 75
1794310644 75
1794310649 77
1794310654 77
1794310659 77
1794310664 77
1794310669 74
1794310674 74
1794310679 74
1794310684 74
1794310689 74
1794310694 74
1794310699 74
1794310704 74
1794310709 74
```
</details>

---

