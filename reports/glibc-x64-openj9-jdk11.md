---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 09:33:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 891 |
| Sample Rate | 14.85/sec |
| Health Score | 928% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 78-84 cores)</summary>

```
1786454939 80
1786454944 80
1786454949 80
1786454954 80
1786454959 80
1786454964 80
1786454969 82
1786454974 82
1786454979 82
1786454984 84
1786454989 84
1786454994 84
1786454999 84
1786455004 84
1786455009 84
1786455014 82
1786455019 82
1786455024 82
1786455029 78
1786455034 78
```
</details>

---

