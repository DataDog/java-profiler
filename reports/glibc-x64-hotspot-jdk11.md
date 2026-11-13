---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:34:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1794587417 29
1794587422 29
1794587427 29
1794587432 29
1794587437 29
1794587442 29
1794587447 29
1794587452 29
1794587457 29
1794587462 29
1794587467 29
1794587472 29
1794587477 27
1794587482 27
1794587487 27
1794587492 27
1794587497 27
1794587502 27
1794587507 27
1794587512 27
```
</details>

---

