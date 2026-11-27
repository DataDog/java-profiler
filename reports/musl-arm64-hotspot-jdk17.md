---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 11:54:57 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 7 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1795798256 52
1795798261 52
1795798266 52
1795798271 52
1795798276 52
1795798281 52
1795798286 52
1795798291 52
1795798296 52
1795798301 52
1795798306 52
1795798311 52
1795798316 52
1795798321 52
1795798326 52
1795798331 52
1795798336 52
1795798341 52
1795798346 52
1795798351 64
```
</details>

---

