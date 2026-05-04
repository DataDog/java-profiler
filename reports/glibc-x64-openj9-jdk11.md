---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-04 04:47:51 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1777884071 76
1777884076 76
1777884081 76
1777884086 76
1777884091 76
1777884096 76
1777884101 76
1777884106 76
1777884111 78
1777884116 78
1777884121 78
1777884126 78
1777884131 78
1777884136 78
1777884141 78
1777884146 78
1777884151 78
1777884156 78
1777884161 76
1777884166 76
```
</details>

---

