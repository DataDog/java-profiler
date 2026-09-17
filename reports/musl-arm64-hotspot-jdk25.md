---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 13:55:48 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 12-17 cores)</summary>

```
1789667413 12
1789667418 12
1789667423 12
1789667428 12
1789667433 12
1789667438 12
1789667443 12
1789667448 12
1789667453 12
1789667458 12
1789667463 12
1789667468 12
1789667473 12
1789667478 12
1789667483 12
1789667488 12
1789667493 12
1789667498 12
1789667503 12
1789667508 12
```
</details>

---

