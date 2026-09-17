---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 14:20:10 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 10 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 37-40 cores)</summary>

```
1789668942 40
1789668947 40
1789668952 40
1789668957 40
1789668962 40
1789668967 40
1789668972 40
1789668977 40
1789668982 40
1789668987 40
1789668992 40
1789668997 40
1789669002 40
1789669007 40
1789669012 40
1789669017 40
1789669022 37
1789669027 37
1789669032 37
1789669037 37
```
</details>

---

