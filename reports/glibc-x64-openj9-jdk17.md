---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 07:55:49 EST

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 77-88 cores)</summary>

```
1794487808 88
1794487813 88
1794487818 88
1794487823 88
1794487828 88
1794487833 88
1794487838 86
1794487843 86
1794487848 77
1794487853 77
1794487858 77
1794487863 77
1794487868 77
1794487873 77
1794487878 77
1794487883 77
1794487888 77
1794487893 77
1794487898 77
1794487904 77
```
</details>

---

