---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 18:20:14 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 8 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 79-96 cores)</summary>

```
1794438872 79
1794438877 79
1794438882 79
1794438887 79
1794438892 79
1794438897 79
1794438902 79
1794438907 79
1794438913 79
1794438918 79
1794438923 79
1794438928 79
1794438933 79
1794438938 96
1794438943 96
1794438948 96
1794438953 96
1794438958 96
1794438963 96
1794438968 96
```
</details>

---

