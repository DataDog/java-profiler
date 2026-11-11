---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 05:29:40 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794392651 48
1794392656 48
1794392661 48
1794392666 48
1794392671 48
1794392676 48
1794392681 48
1794392686 48
1794392691 48
1794392696 48
1794392701 48
1794392706 48
1794392711 48
1794392716 48
1794392721 48
1794392726 48
1794392731 48
1794392736 48
1794392741 48
1794392746 48
```
</details>

---

