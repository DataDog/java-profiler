---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 09:29:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 308 |
| Sample Rate | 5.13/sec |
| Health Score | 321% |
| Threads | 10 |
| Allocations | 128 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (5 unique values: 37-48 cores)</summary>

```
1792761894 48
1792761899 48
1792761904 46
1792761909 46
1792761914 46
1792761919 46
1792761924 44
1792761929 44
1792761934 44
1792761939 44
1792761944 39
1792761949 39
1792761954 37
1792761959 37
1792761964 37
1792761969 37
1792761974 37
1792761979 37
1792761984 37
1792761989 37
```
</details>

---

