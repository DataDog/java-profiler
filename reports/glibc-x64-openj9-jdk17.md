---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-13 16:15:58 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (5 unique values: 76-96 cores)</summary>

```
1786651875 92
1786651880 92
1786651885 92
1786651890 92
1786651895 92
1786651900 92
1786651905 94
1786651910 94
1786651915 94
1786651920 96
1786651925 96
1786651930 96
1786651935 96
1786651940 96
1786651945 96
1786651950 94
1786651955 94
1786651960 94
1786651965 92
1786651970 92
```
</details>

---

