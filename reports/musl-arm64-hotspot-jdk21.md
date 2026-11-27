---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-27 16:25:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 29 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1795814493 32
1795814498 32
1795814503 32
1795814509 32
1795814514 32
1795814519 32
1795814524 32
1795814529 32
1795814534 32
1795814539 32
1795814544 32
1795814549 32
1795814554 32
1795814559 32
1795814564 32
1795814569 32
1795814574 32
1795814579 32
1795814584 32
1795814589 32
```
</details>

---

