---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-29 12:43:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 17.23/sec |
| Health Score | 1077% |
| Threads | 10 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ⚠️
| Metric | Value |
|--------|-------|
| Status | N/A |
| CPU Samples | N/A |
| Sample Rate | N/A/sec |
| Health Score | N/A% |
| Threads | N/A |
| Allocations | N/A |

<details>
<summary>CPU Timeline (3 unique values: 51-61 cores)</summary>

```
1769708286 51
1769708291 51
1769708296 51
1769708301 51
1769708306 51
1769708311 51
1769708316 60
1769708321 60
1769708326 60
1769708331 60
1769708336 60
1769708341 60
1769708346 60
1769708351 60
1769708356 60
1769708361 60
1769708366 60
1769708371 60
1769708376 60
1769708381 60
```
</details>

---

