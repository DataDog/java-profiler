---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 08:52:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 85-92 cores)</summary>

```
1794836779 92
1794836784 92
1794836789 92
1794836794 92
1794836799 92
1794836804 92
1794836809 92
1794836814 88
1794836819 88
1794836824 88
1794836829 85
1794836834 85
1794836839 85
1794836844 85
1794836849 85
1794836854 85
1794836859 85
1794836864 85
1794836869 85
1794836874 85
```
</details>

---

