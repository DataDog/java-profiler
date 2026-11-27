---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 16:25:34 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 9 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1795814479 32
1795814484 32
1795814489 32
1795814494 32
1795814499 32
1795814504 32
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
```
</details>

---

