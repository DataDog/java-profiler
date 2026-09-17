---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 13:55:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 8 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1789667346 30
1789667351 30
1789667356 32
1789667361 32
1789667366 32
1789667371 32
1789667376 32
1789667381 32
1789667386 32
1789667391 32
1789667396 32
1789667401 32
1789667406 32
1789667411 32
1789667416 32
1789667421 32
1789667426 32
1789667431 32
1789667436 32
1789667441 32
```
</details>

---

