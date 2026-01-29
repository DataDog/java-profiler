---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-29 08:17:25 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 23.60/sec |
| Health Score | 1475% |
| Threads | 10 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 24.67/sec |
| Health Score | 1542% |
| Threads | 12 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1769692332 86
1769692337 86
1769692342 86
1769692347 86
1769692352 86
1769692357 88
1769692363 88
1769692368 88
1769692373 88
1769692378 88
1769692383 88
1769692388 86
1769692393 86
1769692398 86
1769692403 86
1769692408 86
1769692413 86
1769692418 86
1769692423 86
1769692428 86
```
</details>

---

