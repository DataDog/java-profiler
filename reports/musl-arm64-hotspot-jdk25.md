---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 03:39:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1791531264 24
1791531269 24
1791531274 29
1791531279 29
1791531284 29
1791531289 29
1791531294 29
1791531299 29
1791531304 29
1791531309 29
1791531314 29
1791531319 29
1791531324 29
1791531329 29
1791531334 29
1791531339 29
1791531344 29
1791531349 29
1791531354 29
1791531359 29
```
</details>

---

