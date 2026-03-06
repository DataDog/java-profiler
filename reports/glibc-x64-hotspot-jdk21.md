---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-06 06:30:57 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 10 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 12 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 72-92 cores)</summary>

```
1772796354 72
1772796359 72
1772796364 72
1772796369 72
1772796374 92
1772796379 92
1772796384 82
1772796389 82
1772796394 82
1772796399 82
1772796404 82
1772796409 82
1772796414 82
1772796419 82
1772796424 84
1772796429 84
1772796434 84
1772796439 84
1772796444 84
1772796449 84
```
</details>

---

