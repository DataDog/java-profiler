---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 10:00:26 EST

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
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1031 |
| Sample Rate | 17.18/sec |
| Health Score | 1074% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793631313 51
1793631318 51
1793631323 51
1793631328 51
1793631333 51
1793631338 51
1793631343 51
1793631348 51
1793631353 51
1793631358 51
1793631363 51
1793631368 51
1793631373 51
1793631378 51
1793631383 51
1793631388 51
1793631393 51
1793631398 51
1793631403 51
1793631408 51
```
</details>

---

