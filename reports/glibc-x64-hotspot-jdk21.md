---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 07:47:07 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 64-71 cores)</summary>

```
1794487368 67
1794487373 65
1794487378 65
1794487383 65
1794487388 65
1794487393 65
1794487398 65
1794487403 65
1794487408 65
1794487413 67
1794487418 67
1794487423 67
1794487428 67
1794487433 67
1794487438 67
1794487443 67
1794487448 67
1794487453 71
1794487458 71
1794487463 71
```
</details>

---

