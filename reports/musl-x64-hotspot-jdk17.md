---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-05 08:22:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 52-62 cores)</summary>

```
1777983465 52
1777983470 52
1777983475 52
1777983480 52
1777983485 52
1777983490 57
1777983495 57
1777983500 57
1777983505 57
1777983510 57
1777983515 57
1777983520 62
1777983525 62
1777983530 62
1777983535 62
1777983540 62
1777983545 62
1777983550 62
1777983555 62
1777983560 62
```
</details>

---

