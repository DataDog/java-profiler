---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 12:33:38 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795022947 46
1795022952 51
1795022957 51
1795022962 51
1795022967 51
1795022972 51
1795022977 51
1795022982 51
1795022987 51
1795022992 51
1795022997 51
1795023002 51
1795023007 51
1795023012 51
1795023017 51
1795023022 51
1795023027 51
1795023032 51
1795023037 51
1795023042 51
```
</details>

---

