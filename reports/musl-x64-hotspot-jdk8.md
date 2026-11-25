---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 06:23:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 77-87 cores)</summary>

```
1795605473 77
1795605478 77
1795605483 83
1795605488 83
1795605493 83
1795605498 83
1795605503 83
1795605508 83
1795605513 85
1795605518 85
1795605523 85
1795605528 83
1795605533 83
1795605538 83
1795605543 83
1795605548 83
1795605553 85
1795605558 85
1795605563 85
1795605568 85
```
</details>

---

