---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 15:36:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 12 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789673443 48
1789673448 48
1789673453 48
1789673458 48
1789673463 48
1789673468 48
1789673473 48
1789673478 48
1789673483 48
1789673488 48
1789673493 48
1789673498 48
1789673503 48
1789673508 48
1789673513 43
1789673518 43
1789673523 43
1789673528 43
1789673533 43
1789673538 43
```
</details>

---

