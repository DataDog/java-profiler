---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-10 17:36:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 11 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1189 |
| Sample Rate | 19.82/sec |
| Health Score | 1239% |
| Threads | 14 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (5 unique values: 71-80 cores)</summary>

```
1770762519 80
1770762524 80
1770762529 80
1770762534 73
1770762539 73
1770762544 73
1770762549 71
1770762554 71
1770762559 71
1770762564 75
1770762569 75
1770762574 74
1770762579 74
1770762584 74
1770762589 74
1770762594 74
1770762600 74
1770762605 74
1770762610 74
1770762615 74
```
</details>

---

