---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 09:25:37 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 13 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (2 unique values: 42-59 cores)</summary>

```
1795702872 42
1795702877 42
1795702882 42
1795702887 42
1795702892 42
1795702897 42
1795702902 42
1795702907 42
1795702912 42
1795702917 42
1795702922 42
1795702927 42
1795702932 42
1795702937 42
1795702942 42
1795702947 42
1795702952 42
1795702957 42
1795702962 42
1795702967 42
```
</details>

---

