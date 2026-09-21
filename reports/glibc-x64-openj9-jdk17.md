---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 05:49:06 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 64-96 cores)</summary>

```
1789983861 76
1789983866 76
1789983871 76
1789983876 76
1789983881 76
1789983886 76
1789983891 76
1789983896 76
1789983901 96
1789983906 96
1789983911 96
1789983916 71
1789983921 71
1789983926 71
1789983931 71
1789983936 71
1789983941 71
1789983946 71
1789983951 71
1789983956 71
```
</details>

---

