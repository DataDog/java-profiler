---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:39:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 59-87 cores)</summary>

```
1795606480 87
1795606485 87
1795606490 87
1795606495 87
1795606500 87
1795606505 87
1795606510 87
1795606515 87
1795606520 87
1795606525 87
1795606530 87
1795606535 87
1795606540 87
1795606545 87
1795606550 87
1795606555 59
1795606560 59
1795606565 59
1795606570 59
1795606575 59
```
</details>

---

