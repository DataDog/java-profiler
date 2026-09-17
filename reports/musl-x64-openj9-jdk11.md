---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 15:41:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 851 |
| Sample Rate | 14.18/sec |
| Health Score | 886% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 18-20 cores)</summary>

```
1789673453 18
1789673458 18
1789673463 18
1789673468 18
1789673473 18
1789673478 20
1789673483 20
1789673488 20
1789673493 20
1789673498 20
1789673503 20
1789673508 20
1789673513 20
1789673518 20
1789673523 20
1789673528 20
1789673533 20
1789673538 20
1789673543 20
1789673548 20
```
</details>

---

