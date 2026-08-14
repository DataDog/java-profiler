---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-14 05:49:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 49-53 cores)</summary>

```
1786700622 53
1786700627 53
1786700632 53
1786700637 53
1786700642 53
1786700647 53
1786700652 53
1786700657 53
1786700662 53
1786700667 53
1786700672 53
1786700677 53
1786700682 53
1786700687 53
1786700692 53
1786700697 53
1786700702 53
1786700707 49
1786700712 49
1786700717 49
```
</details>

---

