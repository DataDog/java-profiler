---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 10:21:04 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 337 |
| Sample Rate | 5.62/sec |
| Health Score | 351% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794323788 48
1794323793 48
1794323798 48
1794323803 48
1794323808 48
1794323813 48
1794323818 48
1794323823 48
1794323828 48
1794323833 48
1794323838 48
1794323843 48
1794323849 48
1794323854 48
1794323859 48
1794323864 48
1794323869 43
1794323874 43
1794323879 43
1794323884 43
```
</details>

---

