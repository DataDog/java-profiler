---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 09:44:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 10 |
| Allocations | 107 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 37-40 cores)</summary>

```
1792676353 40
1792676358 40
1792676363 40
1792676368 40
1792676373 40
1792676378 40
1792676383 40
1792676388 40
1792676393 40
1792676398 40
1792676403 40
1792676408 40
1792676413 40
1792676418 38
1792676423 38
1792676428 38
1792676433 38
1792676438 38
1792676443 38
1792676448 38
```
</details>

---

