---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 05:16:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 8 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770113279 32
1770113284 32
1770113289 32
1770113294 32
1770113300 32
1770113305 32
1770113310 32
1770113315 32
1770113320 32
1770113325 32
1770113330 32
1770113335 32
1770113340 32
1770113345 32
1770113350 32
1770113355 32
1770113360 32
1770113365 30
1770113370 30
1770113375 30
```
</details>

---

