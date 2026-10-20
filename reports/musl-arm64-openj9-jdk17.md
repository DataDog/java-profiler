---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 07:02:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 318 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 10 |
| Allocations | 144 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 15 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1792493904 48
1792493909 48
1792493914 48
1792493919 43
1792493924 43
1792493929 38
1792493934 38
1792493939 38
1792493944 38
1792493949 38
1792493954 38
1792493959 38
1792493964 38
1792493969 38
1792493974 38
1792493979 43
1792493984 43
1792493989 43
1792493994 43
1792493999 43
```
</details>

---

