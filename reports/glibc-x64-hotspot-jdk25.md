---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 17:21:29 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 11 |
| Allocations | 560 |

<details>
<summary>CPU Timeline (3 unique values: 78-82 cores)</summary>

```
1794608242 82
1794608247 82
1794608252 82
1794608257 82
1794608262 82
1794608267 82
1794608272 82
1794608277 82
1794608282 82
1794608287 82
1794608292 82
1794608297 80
1794608302 80
1794608307 80
1794608312 80
1794608317 80
1794608322 78
1794608327 78
1794608332 78
1794608337 78
```
</details>

---

