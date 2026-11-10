---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 13:30:51 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 75-77 cores)</summary>

```
1794334837 77
1794334842 77
1794334847 77
1794334852 77
1794334857 77
1794334862 77
1794334867 77
1794334872 77
1794334877 77
1794334882 77
1794334887 77
1794334892 77
1794334897 77
1794334902 77
1794334907 77
1794334912 77
1794334917 75
1794334922 75
1794334928 75
1794334933 75
```
</details>

---

