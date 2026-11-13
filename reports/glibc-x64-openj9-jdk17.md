---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:34:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 74-86 cores)</summary>

```
1794587396 76
1794587401 76
1794587406 76
1794587411 76
1794587416 76
1794587422 76
1794587427 76
1794587432 76
1794587437 76
1794587442 76
1794587447 76
1794587452 74
1794587457 74
1794587462 74
1794587467 74
1794587472 76
1794587477 76
1794587482 76
1794587487 76
1794587492 76
```
</details>

---

