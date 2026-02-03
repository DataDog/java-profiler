---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 05:16:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 21-32 cores)</summary>

```
1770113274 21
1770113279 21
1770113284 21
1770113289 21
1770113294 21
1770113299 21
1770113304 21
1770113309 21
1770113314 21
1770113319 21
1770113324 32
1770113329 32
1770113334 32
1770113339 32
1770113344 32
1770113349 32
1770113354 32
1770113359 32
1770113364 32
1770113369 32
```
</details>

---

