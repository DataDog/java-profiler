---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 21:18:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
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
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794795237 32
1794795242 32
1794795247 32
1794795252 32
1794795257 32
1794795262 32
1794795267 32
1794795272 32
1794795277 32
1794795282 32
1794795287 32
1794795292 32
1794795297 32
1794795302 32
1794795307 32
1794795312 32
1794795317 32
1794795322 32
1794795327 32
1794795332 32
```
</details>

---

