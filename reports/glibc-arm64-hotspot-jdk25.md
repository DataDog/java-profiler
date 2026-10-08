---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 06:54:10 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791456661 40
1791456666 40
1791456671 40
1791456676 40
1791456681 40
1791456686 40
1791456691 40
1791456696 40
1791456701 40
1791456706 40
1791456711 40
1791456716 40
1791456721 40
1791456726 40
1791456731 40
1791456736 40
1791456741 40
1791456746 40
1791456751 40
1791456756 40
```
</details>

---

