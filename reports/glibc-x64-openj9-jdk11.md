---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 13:29:10 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794939897 48
1794939902 48
1794939907 48
1794939912 48
1794939917 48
1794939922 48
1794939927 48
1794939932 46
1794939937 46
1794939942 46
1794939947 46
1794939952 46
1794939957 46
1794939962 46
1794939967 46
1794939972 46
1794939977 46
1794939982 46
1794939987 46
1794939992 46
```
</details>

---

