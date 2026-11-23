---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 05:58:00 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (5 unique values: 29-34 cores)</summary>

```
1795431213 34
1795431218 34
1795431223 34
1795431229 33
1795431234 33
1795431239 31
1795431244 31
1795431249 31
1795431254 31
1795431259 31
1795431264 31
1795431269 31
1795431274 31
1795431279 30
1795431284 30
1795431289 29
1795431294 29
1795431299 29
1795431304 31
1795431309 31
```
</details>

---

