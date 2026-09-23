---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 10:27:21 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 11 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790173274 50
1790173279 50
1790173284 50
1790173289 50
1790173294 50
1790173299 50
1790173304 50
1790173309 50
1790173314 50
1790173319 50
1790173324 50
1790173329 50
1790173334 50
1790173339 50
1790173344 50
1790173349 50
1790173354 50
1790173359 50
1790173364 50
1790173369 50
```
</details>

---

