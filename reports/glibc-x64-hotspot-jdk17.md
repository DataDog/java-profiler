---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 07:47:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (5 unique values: 64-71 cores)</summary>

```
1794487358 66
1794487363 66
1794487368 66
1794487373 66
1794487378 66
1794487383 66
1794487388 68
1794487393 68
1794487398 68
1794487403 71
1794487408 71
1794487413 71
1794487418 71
1794487423 67
1794487428 67
1794487433 67
1794487438 67
1794487443 67
1794487448 67
1794487453 67
```
</details>

---

