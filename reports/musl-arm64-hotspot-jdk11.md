---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 10:30:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 9 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795793227 64
1795793232 64
1795793237 64
1795793242 64
1795793247 64
1795793252 64
1795793257 64
1795793262 64
1795793267 64
1795793272 64
1795793277 64
1795793282 64
1795793287 64
1795793292 64
1795793297 64
1795793303 64
1795793308 64
1795793313 64
1795793318 64
1795793323 64
```
</details>

---

