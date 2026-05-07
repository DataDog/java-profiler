---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 10:58:44 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 11 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (4 unique values: 46-64 cores)</summary>

```
1778165592 46
1778165597 46
1778165602 46
1778165607 46
1778165612 46
1778165617 46
1778165622 46
1778165627 46
1778165632 46
1778165637 46
1778165642 46
1778165647 46
1778165652 46
1778165657 46
1778165662 46
1778165667 46
1778165672 46
1778165677 46
1778165682 51
1778165687 51
```
</details>

---

