---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-29 12:43:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 20.23/sec |
| Health Score | 1264% |
| Threads | 9 |
| Allocations | 322 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 26.07/sec |
| Health Score | 1629% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (5 unique values: 42-65 cores)</summary>

```
1769708259 42
1769708264 46
1769708269 46
1769708274 46
1769708279 46
1769708284 46
1769708289 44
1769708294 44
1769708299 46
1769708304 46
1769708309 46
1769708314 46
1769708319 51
1769708324 51
1769708329 51
1769708334 51
1769708339 51
1769708344 51
1769708349 65
1769708354 65
```
</details>

---

