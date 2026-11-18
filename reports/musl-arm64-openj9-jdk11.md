---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:25:46 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 169 |
| Sample Rate | 2.82/sec |
| Health Score | 176% |
| Threads | 10 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1795015288 51
1795015293 51
1795015298 51
1795015303 64
1795015308 64
1795015313 64
1795015318 51
1795015323 51
1795015328 51
1795015333 51
1795015338 51
1795015343 51
1795015348 51
1795015353 51
1795015358 51
1795015363 51
1795015368 51
1795015373 51
1795015378 51
1795015383 51
```
</details>

---

