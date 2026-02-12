---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-12 13:12:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 805 |
| Sample Rate | 13.42/sec |
| Health Score | 839% |
| Threads | 12 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 79-91 cores)</summary>

```
1770919620 91
1770919625 91
1770919630 91
1770919635 82
1770919640 82
1770919646 82
1770919651 82
1770919656 82
1770919661 82
1770919666 82
1770919671 82
1770919676 82
1770919681 82
1770919686 82
1770919691 82
1770919696 82
1770919701 82
1770919706 82
1770919711 82
1770919716 82
```
</details>

---

