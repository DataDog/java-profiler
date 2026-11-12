---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:09:38 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 9 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 39-52 cores)</summary>

```
1794495888 39
1794495893 39
1794495898 39
1794495903 39
1794495908 39
1794495913 39
1794495918 39
1794495923 39
1794495928 39
1794495933 39
1794495938 39
1794495943 39
1794495948 52
1794495953 52
1794495958 52
1794495963 52
1794495968 52
1794495973 52
1794495978 52
1794495983 52
```
</details>

---

