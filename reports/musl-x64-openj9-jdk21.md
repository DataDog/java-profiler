---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 09:20:30 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 10 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (4 unique values: 69-87 cores)</summary>

```
1778591643 87
1778591648 87
1778591653 87
1778591658 87
1778591663 87
1778591668 87
1778591673 87
1778591678 69
1778591683 69
1778591688 69
1778591693 69
1778591698 69
1778591703 69
1778591708 69
1778591713 69
1778591718 78
1778591723 78
1778591728 78
1778591733 78
1778591738 78
```
</details>

---

