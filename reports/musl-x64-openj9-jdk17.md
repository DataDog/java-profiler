---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-22 15:55:20 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 66-75 cores)</summary>

```
1795380678 73
1795380683 73
1795380688 73
1795380693 71
1795380698 71
1795380703 71
1795380708 71
1795380713 71
1795380718 71
1795380723 71
1795380728 71
1795380733 73
1795380738 73
1795380743 73
1795380748 75
1795380753 75
1795380758 75
1795380763 75
1795380768 75
1795380774 75
```
</details>

---

