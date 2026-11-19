---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 06:28:26 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 9 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1795087355 49
1795087360 49
1795087365 49
1795087370 49
1795087375 49
1795087380 51
1795087385 51
1795087390 51
1795087395 51
1795087400 49
1795087405 49
1795087410 49
1795087415 49
1795087420 49
1795087425 49
1795087430 49
1795087435 49
1795087440 49
1795087445 49
1795087450 49
```
</details>

---

