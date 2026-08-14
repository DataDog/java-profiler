---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-14 05:49:17 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1786700595 40
1786700600 40
1786700605 40
1786700610 40
1786700615 40
1786700620 43
1786700625 43
1786700630 43
1786700635 43
1786700640 38
1786700645 38
1786700650 38
1786700655 38
1786700660 38
1786700665 43
1786700670 43
1786700675 43
1786700680 43
1786700685 43
1786700690 43
```
</details>

---

