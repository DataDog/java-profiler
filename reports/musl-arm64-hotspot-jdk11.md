---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 08:55:21 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 10 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (3 unique values: 22-48 cores)</summary>

```
1794577833 22
1794577838 22
1794577843 22
1794577848 22
1794577853 22
1794577858 22
1794577863 22
1794577868 35
1794577873 35
1794577878 35
1794577883 35
1794577888 35
1794577893 35
1794577898 35
1794577903 35
1794577908 35
1794577913 35
1794577919 48
1794577924 48
1794577929 48
```
</details>

---

