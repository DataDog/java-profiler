---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:28:44 EST

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
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1024 |
| Sample Rate | 17.07/sec |
| Health Score | 1067% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 49-71 cores)</summary>

```
1794392598 71
1794392603 71
1794392608 71
1794392613 71
1794392618 71
1794392623 71
1794392628 71
1794392633 71
1794392638 71
1794392643 71
1794392648 71
1794392653 49
1794392658 49
1794392663 49
1794392668 49
1794392673 49
1794392678 49
1794392683 49
1794392688 49
1794392693 49
```
</details>

---

