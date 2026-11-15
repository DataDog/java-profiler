---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-14 21:04:20 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794708000 51
1794708005 51
1794708010 51
1794708015 51
1794708020 51
1794708025 51
1794708030 51
1794708035 51
1794708040 51
1794708045 51
1794708050 51
1794708055 51
1794708060 51
1794708065 51
1794708070 51
1794708075 51
1794708080 51
1794708085 51
1794708090 51
1794708095 51
```
</details>

---

