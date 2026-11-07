---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 22:03:14 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 10 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (3 unique values: 60-68 cores)</summary>

```
1794020220 60
1794020225 60
1794020230 60
1794020235 60
1794020240 62
1794020245 62
1794020250 62
1794020255 62
1794020260 62
1794020265 62
1794020271 68
1794020276 68
1794020281 68
1794020286 68
1794020291 68
1794020296 68
1794020301 68
1794020306 68
1794020311 68
1794020316 68
```
</details>

---

