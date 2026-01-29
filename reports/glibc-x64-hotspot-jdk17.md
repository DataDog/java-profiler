---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 12:43:39 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 19.67/sec |
| Health Score | 1229% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 20.33/sec |
| Health Score | 1271% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 65-75 cores)</summary>

```
1769708264 65
1769708269 65
1769708274 65
1769708279 65
1769708284 65
1769708289 65
1769708294 65
1769708299 65
1769708304 65
1769708309 65
1769708314 65
1769708319 65
1769708324 65
1769708329 65
1769708334 65
1769708339 65
1769708344 65
1769708349 65
1769708354 75
1769708359 75
```
</details>

---

