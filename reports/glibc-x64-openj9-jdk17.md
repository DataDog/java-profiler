---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 08:37:24 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (5 unique values: 71-96 cores)</summary>

```
1790771564 73
1790771569 73
1790771574 73
1790771579 71
1790771584 71
1790771589 71
1790771594 71
1790771599 71
1790771604 71
1790771609 73
1790771614 73
1790771619 71
1790771624 71
1790771629 74
1790771634 74
1790771639 74
1790771644 74
1790771649 74
1790771654 94
1790771659 94
```
</details>

---

