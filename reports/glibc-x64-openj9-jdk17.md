---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:02:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 61-66 cores)</summary>

```
1795618632 64
1795618637 64
1795618642 66
1795618647 66
1795618652 66
1795618657 66
1795618662 66
1795618667 66
1795618672 66
1795618677 61
1795618682 61
1795618687 61
1795618692 61
1795618697 61
1795618702 61
1795618707 61
1795618712 61
1795618717 61
1795618722 61
1795618727 61
```
</details>

---

