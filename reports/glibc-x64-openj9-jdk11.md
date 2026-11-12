---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:58:59 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (6 unique values: 63-84 cores)</summary>

```
1794480744 63
1794480749 63
1794480754 63
1794480759 63
1794480764 63
1794480769 84
1794480774 84
1794480779 68
1794480784 68
1794480789 68
1794480794 68
1794480799 68
1794480804 68
1794480809 66
1794480814 66
1794480819 66
1794480824 73
1794480829 73
1794480834 73
1794480839 73
```
</details>

---

