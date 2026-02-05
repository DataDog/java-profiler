---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-05 15:03:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (4 unique values: 70-89 cores)</summary>

```
1770321569 89
1770321574 89
1770321579 89
1770321584 89
1770321589 89
1770321594 89
1770321599 89
1770321604 89
1770321609 74
1770321614 74
1770321619 74
1770321624 74
1770321629 74
1770321634 74
1770321639 74
1770321644 74
1770321649 74
1770321654 74
1770321659 74
1770321664 74
```
</details>

---

