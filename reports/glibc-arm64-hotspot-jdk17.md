---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 13:25:48 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1795803656 24
1795803661 24
1795803666 24
1795803671 29
1795803676 29
1795803681 29
1795803686 29
1795803691 34
1795803696 34
1795803701 34
1795803706 34
1795803711 34
1795803716 34
1795803721 34
1795803726 34
1795803731 34
1795803736 34
1795803741 34
1795803746 34
1795803751 34
```
</details>

---

