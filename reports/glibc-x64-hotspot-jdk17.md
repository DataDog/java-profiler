---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:01:29 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 11 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 66-86 cores)</summary>

```
1794585419 86
1794585424 86
1794585429 86
1794585434 86
1794585439 86
1794585444 66
1794585449 66
1794585454 66
1794585459 66
1794585464 66
1794585469 66
1794585474 66
1794585479 66
1794585484 66
1794585489 68
1794585494 68
1794585499 68
1794585504 68
1794585510 68
1794585515 68
```
</details>

---

