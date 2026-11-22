---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 17:10:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 12 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 73-76 cores)</summary>

```
1795385243 73
1795385248 73
1795385253 75
1795385258 75
1795385263 75
1795385268 75
1795385273 75
1795385278 75
1795385283 75
1795385288 75
1795385293 75
1795385298 75
1795385303 75
1795385308 75
1795385313 75
1795385318 75
1795385323 75
1795385328 73
1795385333 73
1795385338 73
```
</details>

---

