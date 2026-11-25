---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:36:30 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 11 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 10 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 16-33 cores)</summary>

```
1795620716 16
1795620721 16
1795620726 16
1795620731 16
1795620736 16
1795620741 16
1795620746 16
1795620751 16
1795620756 16
1795620761 16
1795620766 16
1795620771 16
1795620776 16
1795620781 16
1795620786 16
1795620791 33
1795620796 33
1795620801 33
1795620806 33
1795620811 33
```
</details>

---

