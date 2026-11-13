---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 16:21:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794604676 48
1794604681 48
1794604686 48
1794604691 48
1794604696 48
1794604701 48
1794604706 48
1794604711 48
1794604716 48
1794604721 48
1794604726 48
1794604731 48
1794604736 48
1794604741 48
1794604746 48
1794604751 48
1794604756 48
1794604761 48
1794604766 48
1794604771 48
```
</details>

---

