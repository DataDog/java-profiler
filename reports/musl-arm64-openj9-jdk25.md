---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 04:44:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 9 |
| Allocations | 129 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 14 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (4 unique values: 13-50 cores)</summary>

```
1792139941 13
1792139946 50
1792139952 50
1792139957 50
1792139962 50
1792139967 13
1792139972 13
1792139977 13
1792139982 13
1792139987 14
1792139992 14
1792139997 14
1792140002 14
1792140007 14
1792140012 14
1792140017 14
1792140022 14
1792140027 13
1792140032 13
1792140037 13
```
</details>

---

