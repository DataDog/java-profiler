---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-09 12:30:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 12 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1794245041 90
1794245046 90
1794245051 90
1794245056 90
1794245061 90
1794245066 96
1794245071 96
1794245076 96
1794245081 94
1794245086 94
1794245091 94
1794245096 94
1794245101 94
1794245106 94
1794245111 94
1794245116 94
1794245121 94
1794245126 94
1794245131 96
1794245136 96
```
</details>

---

