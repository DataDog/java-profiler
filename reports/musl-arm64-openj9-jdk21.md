---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 11:34:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 13 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (2 unique values: 29-50 cores)</summary>

```
1790090893 50
1790090898 50
1790090903 50
1790090908 50
1790090913 50
1790090918 50
1790090923 50
1790090928 29
1790090933 29
1790090938 29
1790090943 29
1790090948 29
1790090953 29
1790090958 29
1790090963 29
1790090968 29
1790090973 29
1790090978 29
1790090983 29
1790090988 29
```
</details>

---

