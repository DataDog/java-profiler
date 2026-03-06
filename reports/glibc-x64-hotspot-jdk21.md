---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-06 11:13:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 10 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 12 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (2 unique values: 61-64 cores)</summary>

```
1772813282 61
1772813287 64
1772813292 64
1772813297 64
1772813302 64
1772813307 64
1772813312 64
1772813317 64
1772813322 64
1772813327 64
1772813332 64
1772813337 64
1772813342 64
1772813347 64
1772813352 64
1772813357 64
1772813362 64
1772813367 64
1772813372 64
1772813377 64
```
</details>

---

