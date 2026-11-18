---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:55:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 317 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 64-70 cores)</summary>

```
1795027793 70
1795027798 70
1795027803 70
1795027808 70
1795027813 70
1795027818 70
1795027823 70
1795027828 70
1795027833 70
1795027838 70
1795027843 70
1795027848 70
1795027853 70
1795027858 70
1795027863 68
1795027868 68
1795027873 68
1795027878 66
1795027883 66
1795027888 66
```
</details>

---

