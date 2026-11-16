---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 13:04:56 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794851879 36
1794851884 36
1794851889 36
1794851894 36
1794851899 48
1794851904 48
1794851909 48
1794851914 48
1794851919 48
1794851924 48
1794851929 48
1794851934 48
1794851939 48
1794851944 48
1794851949 48
1794851954 48
1794851959 48
1794851964 48
1794851969 48
1794851974 48
```
</details>

---

