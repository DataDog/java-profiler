---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 15:55:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (4 unique values: 34-40 cores)</summary>

```
1795380689 34
1795380694 34
1795380699 34
1795380704 34
1795380709 34
1795380714 34
1795380719 36
1795380724 36
1795380729 36
1795380734 36
1795380739 36
1795380744 36
1795380749 36
1795380754 36
1795380759 38
1795380764 38
1795380769 40
1795380774 40
1795380779 40
1795380784 40
```
</details>

---

