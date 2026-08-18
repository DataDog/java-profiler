---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 21:38:41 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 79-96 cores)</summary>

```
1787016894 79
1787016899 79
1787016904 96
1787016909 96
1787016914 96
1787016919 96
1787016924 96
1787016929 96
1787016934 96
1787016939 96
1787016944 96
1787016949 96
1787016954 96
1787016959 96
1787016964 96
1787016969 96
1787016974 96
1787016979 96
1787016984 96
1787016989 96
```
</details>

---

