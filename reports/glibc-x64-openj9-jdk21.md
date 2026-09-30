---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 07:31:55 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 89-94 cores)</summary>

```
1790767693 94
1790767698 94
1790767703 94
1790767708 94
1790767713 92
1790767718 92
1790767723 92
1790767728 92
1790767733 92
1790767738 92
1790767743 92
1790767748 92
1790767753 94
1790767758 94
1790767763 94
1790767768 94
1790767774 94
1790767779 94
1790767784 94
1790767789 89
```
</details>

---

