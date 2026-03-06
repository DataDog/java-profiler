---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-06 06:13:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (5 unique values: 21-27 cores)</summary>

```
1772795222 26
1772795227 24
1772795232 24
1772795237 26
1772795242 26
1772795247 21
1772795252 21
1772795257 21
1772795262 21
1772795267 21
1772795272 21
1772795277 21
1772795282 21
1772795287 23
1772795292 23
1772795297 23
1772795302 23
1772795307 23
1772795312 23
1772795317 27
```
</details>

---

