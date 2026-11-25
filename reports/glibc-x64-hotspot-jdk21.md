---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:23:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 83-96 cores)</summary>

```
1795605473 83
1795605478 83
1795605483 83
1795605488 83
1795605493 83
1795605498 83
1795605503 83
1795605508 83
1795605513 83
1795605518 83
1795605523 83
1795605528 83
1795605533 83
1795605538 83
1795605543 87
1795605548 87
1795605553 87
1795605558 87
1795605563 87
1795605568 96
```
</details>

---

