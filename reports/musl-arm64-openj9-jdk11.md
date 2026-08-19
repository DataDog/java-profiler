---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-19 10:53:47 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (5 unique values: 34-44 cores)</summary>

```
1787150848 38
1787150853 38
1787150859 38
1787150864 38
1787150869 38
1787150874 38
1787150879 38
1787150884 38
1787150889 43
1787150894 43
1787150899 44
1787150904 44
1787150909 44
1787150914 44
1787150919 44
1787150924 44
1787150929 44
1787150934 44
1787150939 34
1787150944 34
```
</details>

---

