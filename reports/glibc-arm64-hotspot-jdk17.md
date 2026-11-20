---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 08:32:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 35-50 cores)</summary>

```
1795181310 35
1795181315 35
1795181320 35
1795181325 35
1795181330 35
1795181335 35
1795181340 35
1795181345 35
1795181350 35
1795181355 35
1795181360 50
1795181365 50
1795181370 50
1795181375 50
1795181380 50
1795181385 50
1795181390 50
1795181395 50
1795181400 50
1795181405 50
```
</details>

---

