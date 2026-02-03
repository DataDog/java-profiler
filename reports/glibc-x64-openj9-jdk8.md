---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-02-03 05:16:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770113254 32
1770113259 32
1770113264 32
1770113269 32
1770113274 32
1770113279 32
1770113284 32
1770113289 32
1770113294 32
1770113299 32
1770113304 32
1770113309 32
1770113314 32
1770113319 32
1770113324 27
1770113329 27
1770113334 27
1770113339 27
1770113344 27
1770113349 27
```
</details>

---

