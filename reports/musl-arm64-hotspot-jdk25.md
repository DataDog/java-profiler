---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 05:30:25 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 11 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1794997494 44
1794997499 44
1794997504 44
1794997509 44
1794997514 44
1794997519 44
1794997524 44
1794997529 44
1794997534 44
1794997539 44
1794997544 44
1794997549 44
1794997554 44
1794997559 44
1794997564 44
1794997569 44
1794997574 44
1794997579 44
1794997584 44
1794997589 44
```
</details>

---

