---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 13:05:37 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 63-96 cores)</summary>

```
1793642458 92
1793642463 92
1793642468 92
1793642473 92
1793642478 94
1793642483 94
1793642488 94
1793642493 94
1793642498 96
1793642503 96
1793642508 96
1793642513 96
1793642518 96
1793642523 96
1793642528 96
1793642533 96
1793642538 96
1793642543 96
1793642548 96
1793642553 96
```
</details>

---

