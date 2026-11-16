---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 15:45:18 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 987 |
| Sample Rate | 16.45/sec |
| Health Score | 1028% |
| Threads | 12 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 66-71 cores)</summary>

```
1794861603 71
1794861608 71
1794861613 71
1794861618 71
1794861623 71
1794861628 71
1794861633 71
1794861638 71
1794861644 71
1794861649 66
1794861654 66
1794861659 66
1794861664 66
1794861669 66
1794861674 66
1794861679 66
1794861684 66
1794861689 66
1794861694 66
1794861699 66
```
</details>

---

