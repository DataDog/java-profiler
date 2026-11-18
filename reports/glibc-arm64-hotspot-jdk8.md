---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 12:33:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 313 |
| Sample Rate | 5.22/sec |
| Health Score | 326% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795022922 46
1795022927 46
1795022932 46
1795022937 46
1795022942 46
1795022947 46
1795022952 46
1795022957 46
1795022962 46
1795022967 51
1795022972 51
1795022977 46
1795022982 46
1795022987 46
1795022992 46
1795022997 46
1795023002 46
1795023007 46
1795023012 46
1795023017 46
```
</details>

---

