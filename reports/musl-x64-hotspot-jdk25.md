---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 00:03:33 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (2 unique values: 50-59 cores)</summary>

```
1795496339 59
1795496344 59
1795496349 59
1795496354 59
1795496359 59
1795496364 59
1795496369 59
1795496374 59
1795496379 59
1795496384 59
1795496389 50
1795496394 50
1795496399 50
1795496404 50
1795496410 50
1795496415 50
1795496420 50
1795496425 50
1795496430 50
1795496435 50
```
</details>

---

