---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 05:21:39 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 857 |
| Sample Rate | 14.28/sec |
| Health Score | 892% |
| Threads | 10 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (4 unique values: 78-89 cores)</summary>

```
1794824238 78
1794824243 78
1794824248 79
1794824253 79
1794824258 79
1794824263 81
1794824268 81
1794824273 89
1794824278 89
1794824283 89
1794824288 89
1794824294 89
1794824299 89
1794824304 89
1794824309 89
1794824314 89
1794824319 89
1794824324 89
1794824329 89
1794824334 89
```
</details>

---

