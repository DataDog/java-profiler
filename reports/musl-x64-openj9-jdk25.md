---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 05:56:29 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (5 unique values: 62-68 cores)</summary>

```
1795171826 68
1795171831 68
1795171836 68
1795171841 68
1795171846 66
1795171851 66
1795171856 66
1795171861 66
1795171866 66
1795171871 66
1795171876 64
1795171881 64
1795171886 62
1795171891 62
1795171896 67
1795171901 67
1795171906 67
1795171911 67
1795171916 67
1795171921 67
```
</details>

---

