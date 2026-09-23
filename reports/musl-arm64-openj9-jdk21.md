---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 11:34:40 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 10 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (4 unique values: 33-48 cores)</summary>

```
1790177332 48
1790177337 33
1790177342 33
1790177347 33
1790177352 33
1790177357 33
1790177362 33
1790177367 33
1790177372 33
1790177377 33
1790177382 33
1790177387 33
1790177392 33
1790177397 38
1790177402 38
1790177407 43
1790177412 43
1790177417 48
1790177422 48
1790177427 48
```
</details>

---

