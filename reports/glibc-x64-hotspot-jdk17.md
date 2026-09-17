---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 15:41:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1789673443 92
1789673448 92
1789673453 92
1789673458 92
1789673463 92
1789673468 92
1789673473 92
1789673478 92
1789673483 92
1789673488 90
1789673493 90
1789673498 90
1789673503 90
1789673508 90
1789673513 92
1789673518 92
1789673523 94
1789673528 94
1789673533 94
1789673538 94
```
</details>

---

