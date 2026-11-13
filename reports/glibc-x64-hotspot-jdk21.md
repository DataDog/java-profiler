---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 11:34:30 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (4 unique values: 76-86 cores)</summary>

```
1794587417 86
1794587422 86
1794587427 86
1794587432 86
1794587437 86
1794587442 86
1794587447 86
1794587452 86
1794587457 86
1794587462 84
1794587467 84
1794587472 84
1794587477 84
1794587482 76
1794587487 76
1794587492 76
1794587497 76
1794587502 76
1794587507 78
1794587512 78
```
</details>

---

