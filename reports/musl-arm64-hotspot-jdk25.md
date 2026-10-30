---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 01:04:36 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793336401 48
1793336406 48
1793336411 48
1793336416 48
1793336421 48
1793336426 48
1793336431 48
1793336436 48
1793336441 48
1793336446 48
1793336451 48
1793336456 48
1793336461 48
1793336466 48
1793336471 48
1793336476 48
1793336481 48
1793336486 48
1793336491 48
1793336496 48
```
</details>

---

