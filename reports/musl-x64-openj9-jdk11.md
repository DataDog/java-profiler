---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 05:48:09 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 84-96 cores)</summary>

```
1786354960 84
1786354965 84
1786354970 86
1786354975 86
1786354980 86
1786354985 86
1786354990 86
1786354995 86
1786355000 86
1786355005 86
1786355010 86
1786355016 86
1786355021 96
1786355026 96
1786355031 96
1786355036 96
1786355041 96
1786355046 96
1786355051 96
1786355056 96
```
</details>

---

