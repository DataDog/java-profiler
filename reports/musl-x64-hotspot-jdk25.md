---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 06:18:34 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 10 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 12 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770117211 32
1770117216 32
1770117221 32
1770117226 32
1770117231 32
1770117236 32
1770117241 32
1770117246 32
1770117251 32
1770117256 32
1770117261 32
1770117266 32
1770117271 30
1770117276 30
1770117281 30
1770117286 30
1770117291 30
1770117296 30
1770117301 30
1770117306 30
```
</details>

---

