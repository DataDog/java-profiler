---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 20:31:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (5 unique values: 23-40 cores)</summary>

```
1795397206 38
1795397211 38
1795397216 36
1795397221 36
1795397226 36
1795397231 36
1795397236 36
1795397241 36
1795397246 36
1795397251 36
1795397256 38
1795397261 38
1795397266 38
1795397271 40
1795397276 40
1795397281 40
1795397286 40
1795397291 40
1795397296 40
1795397301 23
```
</details>

---

