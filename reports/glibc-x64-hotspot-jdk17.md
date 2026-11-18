---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 05:35:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (5 unique values: 38-66 cores)</summary>

```
1794997957 51
1794997962 51
1794997967 51
1794997972 51
1794997977 53
1794997982 53
1794997987 53
1794997992 53
1794997997 53
1794998002 53
1794998007 55
1794998012 55
1794998017 66
1794998022 66
1794998027 66
1794998032 66
1794998037 66
1794998042 66
1794998047 66
1794998052 66
```
</details>

---

