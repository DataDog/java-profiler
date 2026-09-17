---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 14:20:10 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 12 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789668942 46
1789668947 46
1789668952 46
1789668957 46
1789668962 46
1789668967 46
1789668972 46
1789668977 46
1789668982 46
1789668987 46
1789668992 46
1789668997 46
1789669002 46
1789669007 46
1789669012 46
1789669017 46
1789669022 46
1789669027 46
1789669032 46
1789669037 46
```
</details>

---

