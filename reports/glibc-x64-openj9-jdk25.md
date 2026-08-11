---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 09:33:15 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 87-92 cores)</summary>

```
1786454929 87
1786454934 89
1786454939 89
1786454944 89
1786454949 89
1786454954 89
1786454959 89
1786454964 89
1786454969 90
1786454974 90
1786454979 90
1786454984 90
1786454989 92
1786454994 92
1786454999 92
1786455004 92
1786455009 92
1786455014 92
1786455019 92
1786455024 92
```
</details>

---

