---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 05:36:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795602683 64
1795602688 64
1795602693 64
1795602698 64
1795602703 64
1795602708 64
1795602713 64
1795602718 64
1795602723 64
1795602728 64
1795602733 64
1795602738 64
1795602743 64
1795602748 64
1795602753 64
1795602759 64
1795602764 64
1795602769 64
1795602774 64
1795602779 64
```
</details>

---

