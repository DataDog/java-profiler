---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:39:36 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 53-78 cores)</summary>

```
1795606480 78
1795606485 70
1795606490 70
1795606495 53
1795606500 53
1795606505 53
1795606510 53
1795606515 53
1795606520 53
1795606525 53
1795606530 53
1795606535 53
1795606540 53
1795606545 53
1795606550 53
1795606555 53
1795606560 53
1795606565 53
1795606570 53
1795606575 53
```
</details>

---

