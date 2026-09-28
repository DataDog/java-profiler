---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-27 21:22:40 EDT

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
| CPU Cores (start) | 7 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 7-12 cores)</summary>

```
1790558270 7
1790558275 7
1790558280 7
1790558285 7
1790558290 7
1790558295 7
1790558300 7
1790558305 7
1790558310 7
1790558315 7
1790558320 7
1790558325 7
1790558330 7
1790558335 7
1790558341 7
1790558346 7
1790558351 7
1790558356 7
1790558361 7
1790558366 7
```
</details>

---

