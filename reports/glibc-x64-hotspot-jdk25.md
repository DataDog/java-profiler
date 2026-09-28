---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-28 10:16:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1790604656 17
1790604661 17
1790604666 17
1790604671 17
1790604676 17
1790604681 17
1790604686 17
1790604691 17
1790604696 17
1790604701 17
1790604706 17
1790604711 17
1790604716 17
1790604721 17
1790604726 17
1790604731 15
1790604736 15
1790604741 15
1790604746 15
1790604751 15
```
</details>

---

