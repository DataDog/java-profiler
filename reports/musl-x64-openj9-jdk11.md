---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:57:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 789 |
| Sample Rate | 13.15/sec |
| Health Score | 822% |
| Threads | 10 |
| Allocations | 573 |

<details>
<summary>CPU Timeline (3 unique values: 73-85 cores)</summary>

```
1794408618 85
1794408623 85
1794408628 85
1794408633 76
1794408638 76
1794408643 76
1794408648 76
1794408653 76
1794408658 76
1794408663 76
1794408668 76
1794408673 76
1794408678 76
1794408683 76
1794408688 76
1794408693 76
1794408698 76
1794408703 76
1794408708 76
1794408713 76
```
</details>

---

