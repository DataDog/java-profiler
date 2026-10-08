---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-08 10:53:15 EDT

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 10 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 49-65 cores)</summary>

```
1791470889 65
1791470894 65
1791470899 65
1791470904 65
1791470909 65
1791470914 65
1791470920 65
1791470925 65
1791470930 65
1791470935 65
1791470940 49
1791470945 49
1791470950 49
1791470955 49
1791470960 49
1791470965 49
1791470970 49
1791470975 49
1791470980 49
1791470985 49
```
</details>

---

