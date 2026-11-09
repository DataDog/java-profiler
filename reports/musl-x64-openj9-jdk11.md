---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 12:30:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 831 |
| Sample Rate | 13.85/sec |
| Health Score | 866% |
| Threads | 9 |
| Allocations | 558 |

<details>
<summary>CPU Timeline (6 unique values: 66-75 cores)</summary>

```
1794245022 66
1794245027 66
1794245032 68
1794245037 68
1794245042 68
1794245047 68
1794245052 68
1794245057 68
1794245062 70
1794245067 70
1794245072 72
1794245077 72
1794245082 72
1794245087 70
1794245092 70
1794245097 70
1794245102 70
1794245107 70
1794245112 70
1794245117 73
```
</details>

---

