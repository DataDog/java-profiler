---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 09:33:15 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 31-33 cores)</summary>

```
1786454937 31
1786454942 31
1786454947 31
1786454952 31
1786454957 31
1786454962 31
1786454967 31
1786454972 31
1786454977 31
1786454982 31
1786454987 31
1786454992 31
1786454997 31
1786455002 33
1786455007 33
1786455012 33
1786455017 33
1786455022 33
1786455027 33
1786455032 33
```
</details>

---

