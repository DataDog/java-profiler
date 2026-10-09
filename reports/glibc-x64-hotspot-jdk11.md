---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-09 03:39:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (6 unique values: 52-86 cores)</summary>

```
1791531212 84
1791531217 84
1791531222 84
1791531227 86
1791531232 86
1791531237 86
1791531242 86
1791531247 66
1791531252 66
1791531257 64
1791531262 64
1791531267 64
1791531272 64
1791531277 64
1791531282 64
1791531287 64
1791531292 64
1791531297 64
1791531302 64
1791531307 64
```
</details>

---

