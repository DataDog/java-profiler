---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 08:44:07 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 8 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (5 unique values: 42-48 cores)</summary>

```
1794836326 42
1794836331 42
1794836336 42
1794836341 42
1794836346 43
1794836351 43
1794836356 43
1794836361 43
1794836366 48
1794836371 48
1794836376 48
1794836381 48
1794836386 48
1794836391 48
1794836397 48
1794836402 48
1794836407 47
1794836412 47
1794836417 47
1794836422 47
```
</details>

---

