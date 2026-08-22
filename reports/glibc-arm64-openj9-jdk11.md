---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-22 09:23:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 13 |
| Allocations | 181 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1787404788 36
1787404793 36
1787404798 36
1787404803 36
1787404808 36
1787404813 36
1787404818 36
1787404823 36
1787404828 36
1787404833 36
1787404838 36
1787404843 36
1787404848 36
1787404853 36
1787404858 34
1787404863 34
1787404868 34
1787404873 34
1787404878 34
1787404883 34
```
</details>

---

