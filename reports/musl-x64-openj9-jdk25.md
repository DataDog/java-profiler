---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 13:49:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 61-62 cores)</summary>

```
1793295779 62
1793295784 62
1793295789 62
1793295794 62
1793295799 62
1793295804 62
1793295809 62
1793295814 62
1793295819 62
1793295824 62
1793295829 62
1793295834 62
1793295839 62
1793295844 62
1793295849 62
1793295854 62
1793295859 62
1793295864 62
1793295869 62
1793295874 62
```
</details>

---

