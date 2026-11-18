---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:06:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 61-81 cores)</summary>

```
1795010495 79
1795010500 79
1795010505 79
1795010510 79
1795010515 79
1795010520 79
1795010525 79
1795010530 79
1795010535 79
1795010540 79
1795010545 79
1795010550 79
1795010555 79
1795010560 79
1795010565 79
1795010570 79
1795010575 81
1795010580 81
1795010585 81
1795010590 63
```
</details>

---

