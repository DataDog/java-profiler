---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 17:21:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794608247 40
1794608252 40
1794608257 40
1794608262 40
1794608267 40
1794608272 40
1794608277 40
1794608282 40
1794608287 40
1794608292 40
1794608297 40
1794608302 40
1794608307 40
1794608312 40
1794608317 40
1794608322 40
1794608327 40
1794608332 40
1794608337 40
1794608342 40
```
</details>

---

