---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:36:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 13 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 31-47 cores)</summary>

```
1795620746 31
1795620751 31
1795620756 47
1795620761 47
1795620766 47
1795620771 47
1795620776 47
1795620781 47
1795620786 47
1795620791 47
1795620796 47
1795620801 47
1795620806 47
1795620811 47
1795620816 47
1795620821 47
1795620826 47
1795620831 47
1795620836 47
1795620841 47
```
</details>

---

