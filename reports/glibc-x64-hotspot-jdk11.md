---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 10:16:36 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 43-51 cores)</summary>

```
1790604650 51
1790604656 47
1790604661 47
1790604666 47
1790604671 47
1790604676 47
1790604681 47
1790604686 47
1790604691 43
1790604696 43
1790604701 43
1790604706 43
1790604711 43
1790604716 43
1790604721 43
1790604726 43
1790604731 43
1790604736 43
1790604741 45
1790604746 45
```
</details>

---

