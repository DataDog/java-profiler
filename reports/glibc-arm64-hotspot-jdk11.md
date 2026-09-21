---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-20 21:19:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 16-48 cores)</summary>

```
1789953293 16
1789953298 16
1789953303 16
1789953308 16
1789953313 16
1789953318 18
1789953323 18
1789953328 18
1789953333 18
1789953338 18
1789953343 18
1789953348 18
1789953353 18
1789953358 18
1789953363 18
1789953368 18
1789953373 18
1789953378 18
1789953383 18
1789953388 18
```
</details>

---

