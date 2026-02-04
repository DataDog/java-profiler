---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-04 09:27:26 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 971 |
| Sample Rate | 16.18/sec |
| Health Score | 1011% |
| Threads | 12 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 68-86 cores)</summary>

```
1770214912 86
1770214917 86
1770214922 86
1770214927 77
1770214932 77
1770214937 77
1770214942 77
1770214947 77
1770214952 77
1770214957 77
1770214962 77
1770214967 77
1770214972 77
1770214977 77
1770214982 77
1770214987 77
1770214992 82
1770214997 82
1770215002 82
1770215007 82
```
</details>

---

