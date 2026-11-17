---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 14:55:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (3 unique values: 70-78 cores)</summary>

```
1794945021 70
1794945026 70
1794945031 75
1794945036 75
1794945041 75
1794945046 75
1794945051 75
1794945056 75
1794945061 75
1794945066 75
1794945071 75
1794945076 75
1794945081 75
1794945086 75
1794945091 75
1794945096 78
1794945101 78
1794945106 78
1794945111 78
1794945116 78
```
</details>

---

