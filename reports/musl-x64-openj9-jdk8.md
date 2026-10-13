---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-13 01:03:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1791867578 75
1791867583 75
1791867588 75
1791867593 75
1791867598 77
1791867603 77
1791867608 77
1791867613 77
1791867618 77
1791867623 77
1791867628 79
1791867633 79
1791867638 79
1791867643 79
1791867648 79
1791867653 79
1791867658 79
1791867663 79
1791867668 79
1791867673 79
```
</details>

---

