---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-29 12:43:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 19.70/sec |
| Health Score | 1231% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 25.07/sec |
| Health Score | 1567% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 40-46 cores)</summary>

```
1769708259 42
1769708264 42
1769708269 42
1769708274 42
1769708279 42
1769708284 40
1769708289 40
1769708294 40
1769708299 40
1769708304 40
1769708309 40
1769708314 40
1769708319 40
1769708324 46
1769708329 46
1769708334 46
1769708339 46
1769708344 44
1769708349 44
1769708355 44
```
</details>

---

