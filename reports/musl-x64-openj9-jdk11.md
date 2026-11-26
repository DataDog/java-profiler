---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:07:06 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 9 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (4 unique values: 80-87 cores)</summary>

```
1795690869 80
1795690874 80
1795690879 80
1795690884 80
1795690889 80
1795690894 80
1795690899 80
1795690904 80
1795690909 80
1795690914 80
1795690919 82
1795690924 82
1795690929 82
1795690934 82
1795690939 82
1795690944 87
1795690949 87
1795690954 87
1795690959 87
1795690964 87
```
</details>

---

