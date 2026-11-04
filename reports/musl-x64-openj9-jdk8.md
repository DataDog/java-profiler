---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-04 13:32:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 356 |
| Sample Rate | 5.93/sec |
| Health Score | 371% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 53-87 cores)</summary>

```
1793816862 87
1793816867 87
1793816872 87
1793816877 87
1793816882 87
1793816887 87
1793816892 87
1793816897 53
1793816902 53
1793816907 53
1793816912 53
1793816917 53
1793816922 53
1793816927 53
1793816932 53
1793816937 53
1793816942 53
1793816947 53
1793816952 53
1793816957 53
```
</details>

---

