---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 08:52:14 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 66-68 cores)</summary>

```
1794836783 66
1794836788 66
1794836793 66
1794836798 66
1794836803 66
1794836808 66
1794836813 66
1794836818 66
1794836823 66
1794836828 66
1794836833 66
1794836838 66
1794836843 68
1794836848 68
1794836853 66
1794836858 66
1794836863 66
1794836868 66
1794836873 66
1794836878 66
```
</details>

---

