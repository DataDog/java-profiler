---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 07:26:37 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 14 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (2 unique values: 43-46 cores)</summary>

```
1795177332 46
1795177337 46
1795177342 46
1795177347 46
1795177352 46
1795177357 46
1795177362 46
1795177367 46
1795177372 46
1795177377 46
1795177382 46
1795177387 46
1795177392 46
1795177397 43
1795177402 43
1795177407 43
1795177412 43
1795177417 43
1795177422 43
1795177427 43
```
</details>

---

