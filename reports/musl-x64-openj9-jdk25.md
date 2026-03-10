---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-10 13:36:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 12 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (5 unique values: 23-30 cores)</summary>

```
1773163865 23
1773163870 23
1773163875 23
1773163880 24
1773163885 24
1773163890 24
1773163895 24
1773163900 26
1773163905 26
1773163910 27
1773163915 27
1773163920 27
1773163925 26
1773163930 26
1773163935 26
1773163940 26
1773163945 26
1773163950 26
1773163955 26
1773163960 26
```
</details>

---

