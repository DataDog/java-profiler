---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 07:09:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 16-38 cores)</summary>

```
1792148618 38
1792148623 38
1792148628 38
1792148633 38
1792148638 38
1792148643 16
1792148648 16
1792148653 16
1792148658 16
1792148663 16
1792148668 16
1792148673 16
1792148678 16
1792148683 16
1792148688 16
1792148693 16
1792148698 16
1792148703 16
1792148708 16
1792148713 16
```
</details>

---

