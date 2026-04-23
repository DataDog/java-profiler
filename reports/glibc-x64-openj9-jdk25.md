---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 14:32:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1776968829 48
1776968834 48
1776968839 48
1776968844 48
1776968849 48
1776968854 46
1776968859 46
1776968864 46
1776968869 48
1776968874 48
1776968879 48
1776968884 48
1776968889 48
1776968894 48
1776968899 48
1776968904 48
1776968909 46
1776968914 46
1776968919 46
1776968924 46
```
</details>

---

