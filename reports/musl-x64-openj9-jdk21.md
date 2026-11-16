---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 10:28:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 66-88 cores)</summary>

```
1794842568 68
1794842573 68
1794842578 68
1794842583 68
1794842588 68
1794842593 68
1794842598 68
1794842603 66
1794842608 66
1794842613 66
1794842618 86
1794842623 86
1794842628 86
1794842633 86
1794842638 86
1794842643 86
1794842648 86
1794842653 86
1794842658 88
1794842663 88
```
</details>

---

