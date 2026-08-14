---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-14 05:49:17 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786700667 64
1786700672 64
1786700677 64
1786700682 64
1786700687 64
1786700692 64
1786700697 64
1786700702 64
1786700707 64
1786700712 64
1786700717 64
1786700722 64
1786700727 64
1786700732 64
1786700737 64
1786700742 64
1786700747 64
1786700752 64
1786700757 64
1786700762 64
```
</details>

---

