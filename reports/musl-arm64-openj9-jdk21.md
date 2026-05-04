---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-03 21:20:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 13 |
| Allocations | 169 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857462 64
1777857467 64
1777857472 64
1777857477 64
1777857482 64
1777857487 64
1777857492 64
1777857497 64
1777857502 64
1777857508 64
1777857513 64
1777857518 64
1777857523 64
1777857528 64
1777857533 64
1777857538 64
1777857543 64
1777857548 64
1777857553 64
1777857558 64
```
</details>

---

