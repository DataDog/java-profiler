---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 06:18:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 9 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (4 unique values: 23-32 cores)</summary>

```
1770117196 23
1770117201 23
1770117206 23
1770117211 23
1770117216 23
1770117221 23
1770117226 23
1770117231 23
1770117236 32
1770117241 32
1770117246 30
1770117251 30
1770117256 28
1770117261 28
1770117266 28
1770117271 28
1770117276 30
1770117281 30
1770117286 30
1770117291 30
```
</details>

---

