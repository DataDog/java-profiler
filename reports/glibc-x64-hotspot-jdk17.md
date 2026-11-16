---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 10:28:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 74-84 cores)</summary>

```
1794842574 78
1794842579 78
1794842584 78
1794842589 78
1794842594 78
1794842599 78
1794842604 78
1794842609 78
1794842614 78
1794842619 76
1794842624 76
1794842629 76
1794842634 76
1794842639 76
1794842644 76
1794842649 74
1794842654 74
1794842659 74
1794842664 74
1794842669 74
```
</details>

---

