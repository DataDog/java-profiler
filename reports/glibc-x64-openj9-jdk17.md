---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 03:31:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 832 |
| Sample Rate | 13.87/sec |
| Health Score | 867% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 86-96 cores)</summary>

```
1789716369 86
1789716374 86
1789716379 86
1789716384 86
1789716389 86
1789716394 86
1789716399 86
1789716404 86
1789716409 86
1789716414 95
1789716419 95
1789716424 95
1789716429 95
1789716434 95
1789716440 95
1789716445 95
1789716450 95
1789716455 95
1789716460 95
1789716465 95
```
</details>

---

