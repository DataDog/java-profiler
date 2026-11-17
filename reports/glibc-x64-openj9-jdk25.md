---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 11:12:50 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 49-66 cores)</summary>

```
1794931728 51
1794931733 51
1794931738 51
1794931743 51
1794931748 51
1794931753 51
1794931758 51
1794931763 51
1794931768 51
1794931773 49
1794931778 49
1794931783 49
1794931788 49
1794931793 49
1794931798 49
1794931803 49
1794931808 49
1794931813 66
1794931818 66
1794931823 66
```
</details>

---

