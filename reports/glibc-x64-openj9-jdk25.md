---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:02:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1795618618 62
1795618623 62
1795618628 62
1795618633 60
1795618638 60
1795618643 60
1795618648 60
1795618653 60
1795618658 60
1795618664 60
1795618669 60
1795618674 62
1795618679 62
1795618684 62
1795618689 62
1795618694 62
1795618699 62
1795618704 62
1795618709 62
1795618714 60
```
</details>

---

