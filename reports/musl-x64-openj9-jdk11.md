---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 09:38:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 34-36 cores)</summary>

```
1792675882 36
1792675887 36
1792675892 36
1792675897 34
1792675902 34
1792675907 34
1792675912 34
1792675917 34
1792675922 34
1792675927 34
1792675932 34
1792675937 34
1792675942 34
1792675947 34
1792675952 34
1792675957 34
1792675962 34
1792675967 34
1792675972 34
1792675977 34
```
</details>

---

