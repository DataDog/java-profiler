---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-01 09:14:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ⚠️
| Metric | Value |
|--------|-------|
| Status | N/A |
| CPU Samples | N/A |
| Sample Rate | N/A/sec |
| Health Score | N/A% |
| Threads | N/A |
| Allocations | N/A |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1777640887 51
1777640892 51
1777640897 51
1777640902 51
1777640907 51
1777640912 51
1777640917 51
1777640922 51
1777640927 51
1777640932 51
1777640937 51
1777640942 51
1777640947 51
1777640952 51
1777640957 51
1777640962 51
1777640967 51
1777640972 56
1777640977 56
1777640982 56
```
</details>

---

