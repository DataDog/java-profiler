---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:59:59 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 44-72 cores)</summary>

```
1795431313 44
1795431318 44
1795431323 44
1795431328 44
1795431333 72
1795431338 72
1795431343 51
1795431348 51
1795431353 51
1795431358 51
1795431363 51
1795431368 51
1795431373 51
1795431378 51
1795431383 51
1795431388 51
1795431393 51
1795431398 51
1795431403 51
1795431408 51
```
</details>

---

