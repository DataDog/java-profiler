---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 06:26:09 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1786357317 51
1786357322 51
1786357327 51
1786357332 51
1786357337 51
1786357342 51
1786357347 51
1786357352 51
1786357357 51
1786357362 51
1786357367 51
1786357372 51
1786357377 51
1786357382 51
1786357387 51
1786357392 51
1786357397 51
1786357402 51
1786357407 51
1786357412 51
```
</details>

---

