---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 16:43:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
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
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1794001213 64
1794001218 64
1794001223 62
1794001228 62
1794001233 62
1794001238 62
1794001243 62
1794001248 62
1794001253 62
1794001258 62
1794001263 62
1794001268 64
1794001273 64
1794001278 64
1794001283 64
1794001288 64
1794001293 64
1794001298 64
1794001303 64
1794001308 64
```
</details>

---

