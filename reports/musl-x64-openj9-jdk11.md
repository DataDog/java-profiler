---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:00:13 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 9 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (5 unique values: 82-94 cores)</summary>

```
1794581673 94
1794581678 94
1794581683 94
1794581688 94
1794581693 94
1794581698 94
1794581703 94
1794581708 94
1794581713 94
1794581718 94
1794581723 94
1794581728 94
1794581733 92
1794581738 92
1794581743 92
1794581748 92
1794581753 85
1794581758 85
1794581763 85
1794581768 87
```
</details>

---

