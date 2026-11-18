---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:06:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 11 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1795010480 81
1795010485 81
1795010490 81
1795010495 81
1795010500 81
1795010505 81
1795010510 81
1795010515 81
1795010520 81
1795010525 81
1795010530 79
1795010535 79
1795010540 79
1795010545 77
1795010550 77
1795010555 77
1795010560 79
1795010565 79
1795010570 79
1795010575 79
```
</details>

---

