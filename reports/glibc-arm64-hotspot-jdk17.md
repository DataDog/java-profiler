---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 03:39:35 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 8 |
| Allocations | 129 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791531247 51
1791531252 51
1791531257 51
1791531262 51
1791531267 51
1791531272 51
1791531277 51
1791531282 51
1791531287 51
1791531292 51
1791531297 46
1791531302 46
1791531307 46
1791531312 46
1791531317 46
1791531322 46
1791531327 46
1791531332 46
1791531337 46
1791531342 46
```
</details>

---

