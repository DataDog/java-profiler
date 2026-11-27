---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-27 11:54:56 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 31-33 cores)</summary>

```
1795798301 31
1795798306 31
1795798311 31
1795798316 31
1795798321 31
1795798326 31
1795798331 31
1795798336 31
1795798341 31
1795798346 31
1795798351 31
1795798356 31
1795798361 31
1795798366 31
1795798371 31
1795798376 31
1795798381 33
1795798386 33
1795798391 33
1795798396 33
```
</details>

---

