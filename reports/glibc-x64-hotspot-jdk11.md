---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:30:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 836 |
| Sample Rate | 13.93/sec |
| Health Score | 871% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 54-57 cores)</summary>

```
1794997499 54
1794997504 54
1794997509 54
1794997514 54
1794997519 54
1794997524 54
1794997529 54
1794997534 54
1794997539 54
1794997544 54
1794997549 57
1794997554 57
1794997559 57
1794997564 57
1794997569 57
1794997574 57
1794997579 57
1794997584 57
1794997589 57
1794997594 57
```
</details>

---

