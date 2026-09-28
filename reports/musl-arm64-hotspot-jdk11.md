---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 10:16:37 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 40-44 cores)</summary>

```
1790604671 43
1790604676 43
1790604681 43
1790604686 43
1790604691 43
1790604696 43
1790604701 43
1790604706 43
1790604711 43
1790604716 44
1790604721 44
1790604726 40
1790604731 40
1790604736 40
1790604741 40
1790604746 40
1790604751 40
1790604756 40
1790604761 40
1790604766 40
```
</details>

---

