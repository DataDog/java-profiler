---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 09:44:16 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 74-82 cores)</summary>

```
1792676343 82
1792676348 82
1792676353 82
1792676358 82
1792676363 82
1792676368 82
1792676373 82
1792676378 74
1792676383 74
1792676388 74
1792676393 74
1792676398 74
1792676403 74
1792676408 74
1792676413 74
1792676418 74
1792676423 74
1792676428 74
1792676433 74
1792676438 74
```
</details>

---

