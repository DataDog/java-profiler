---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 17:08:39 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 8 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 30-46 cores)</summary>

```
1794348268 44
1794348273 44
1794348278 46
1794348283 46
1794348288 46
1794348293 46
1794348298 46
1794348303 46
1794348308 46
1794348313 46
1794348318 46
1794348323 46
1794348328 46
1794348333 46
1794348338 46
1794348343 46
1794348348 30
1794348353 30
1794348358 30
1794348363 30
```
</details>

---

