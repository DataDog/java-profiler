---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 18:15:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (5 unique values: 35-73 cores)</summary>

```
1794352209 35
1794352214 35
1794352219 35
1794352224 35
1794352229 35
1794352234 35
1794352239 35
1794352244 35
1794352249 35
1794352254 35
1794352259 40
1794352264 40
1794352269 40
1794352274 40
1794352279 40
1794352284 40
1794352289 73
1794352294 73
1794352299 71
1794352304 71
```
</details>

---

