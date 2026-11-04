---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 10:58:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 12 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 27-40 cores)</summary>

```
1793807627 38
1793807632 38
1793807637 38
1793807642 38
1793807647 38
1793807652 38
1793807657 38
1793807662 38
1793807667 38
1793807672 38
1793807677 38
1793807682 27
1793807687 27
1793807692 27
1793807697 27
1793807702 27
1793807707 27
1793807712 27
1793807717 27
1793807722 40
```
</details>

---

