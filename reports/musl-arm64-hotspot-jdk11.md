---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 09:26:04 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 35-48 cores)</summary>

```
1792588836 35
1792588841 48
1792588846 48
1792588851 48
1792588856 48
1792588861 48
1792588866 48
1792588871 48
1792588876 48
1792588881 37
1792588886 37
1792588891 37
1792588896 37
1792588901 37
1792588906 37
1792588911 37
1792588916 37
1792588921 37
1792588926 37
1792588931 37
```
</details>

---

