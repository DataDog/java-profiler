---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:47:43 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1790091686 48
1790091691 48
1790091696 48
1790091701 48
1790091706 48
1790091711 48
1790091716 48
1790091721 48
1790091726 48
1790091731 48
1790091736 48
1790091741 48
1790091746 48
1790091751 48
1790091756 48
1790091761 36
1790091766 36
1790091771 36
1790091776 36
1790091781 36
```
</details>

---

