---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-05 08:22:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1048 |
| Sample Rate | 17.47/sec |
| Health Score | 1092% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 77-82 cores)</summary>

```
1777983465 82
1777983470 82
1777983475 82
1777983480 82
1777983485 82
1777983490 82
1777983495 82
1777983500 80
1777983505 80
1777983510 82
1777983515 82
1777983520 77
1777983525 77
1777983530 77
1777983535 77
1777983540 77
1777983545 77
1777983550 77
1777983555 77
1777983560 77
```
</details>

---

