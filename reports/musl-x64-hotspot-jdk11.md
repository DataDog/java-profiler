---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:07:00 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 87-92 cores)</summary>

```
1794848435 92
1794848440 90
1794848445 90
1794848450 90
1794848455 90
1794848460 90
1794848465 90
1794848470 90
1794848475 87
1794848480 87
1794848485 87
1794848490 89
1794848495 89
1794848500 89
1794848505 89
1794848510 89
1794848515 89
1794848520 89
1794848525 89
1794848530 89
```
</details>

---

