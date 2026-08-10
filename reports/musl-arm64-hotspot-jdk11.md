---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 14:37:47 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 11 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1786386832 46
1786386838 46
1786386843 46
1786386848 46
1786386853 46
1786386858 46
1786386863 46
1786386868 46
1786386873 46
1786386878 46
1786386883 46
1786386888 41
1786386893 41
1786386898 41
1786386903 46
1786386908 46
1786386913 46
1786386918 46
1786386923 46
1786386928 46
```
</details>

---

