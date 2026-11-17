---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 11:12:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1794931712 49
1794931717 49
1794931723 49
1794931728 49
1794931733 49
1794931738 49
1794931743 49
1794931748 51
1794931753 51
1794931758 51
1794931763 51
1794931768 51
1794931773 51
1794931778 51
1794931783 51
1794931788 51
1794931793 51
1794931798 51
1794931803 51
1794931808 51
```
</details>

---

