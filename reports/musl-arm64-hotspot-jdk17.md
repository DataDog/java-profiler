---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 09:26:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795702911 33
1795702916 33
1795702921 33
1795702926 33
1795702932 33
1795702937 33
1795702942 33
1795702947 33
1795702952 33
1795702957 64
1795702962 64
1795702967 64
1795702972 64
1795702977 64
1795702982 64
1795702987 64
1795702992 64
1795702997 64
1795703002 64
1795703007 64
```
</details>

---

