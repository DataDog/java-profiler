---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 17:14:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (5 unique values: 44-52 cores)</summary>

```
1795558272 48
1795558277 48
1795558282 48
1795558287 48
1795558292 48
1795558297 48
1795558302 48
1795558307 48
1795558312 48
1795558317 48
1795558322 48
1795558327 46
1795558332 46
1795558337 44
1795558342 44
1795558347 44
1795558352 50
1795558357 50
1795558362 50
1795558367 50
```
</details>

---

