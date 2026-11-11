---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 16:04:53 EST

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
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794430857 51
1794430862 51
1794430867 51
1794430872 51
1794430877 51
1794430882 51
1794430887 51
1794430892 51
1794430897 51
1794430902 51
1794430907 51
1794430912 51
1794430917 51
1794430922 51
1794430927 51
1794430932 51
1794430937 51
1794430942 51
1794430947 51
1794430952 51
```
</details>

---

