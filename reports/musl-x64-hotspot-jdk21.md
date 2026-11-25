---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:02:42 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (5 unique values: 48-87 cores)</summary>

```
1795618609 76
1795618614 76
1795618619 76
1795618624 76
1795618629 76
1795618634 76
1795618639 76
1795618644 76
1795618649 76
1795618654 76
1795618659 76
1795618664 76
1795618669 76
1795618674 76
1795618679 76
1795618684 87
1795618689 87
1795618694 59
1795618699 59
1795618704 59
```
</details>

---

