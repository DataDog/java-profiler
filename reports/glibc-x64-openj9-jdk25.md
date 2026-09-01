---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-01 12:28:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 82-84 cores)</summary>

```
1788279685 84
1788279690 82
1788279695 82
1788279700 82
1788279705 82
1788279710 82
1788279715 82
1788279720 82
1788279725 82
1788279730 84
1788279735 84
1788279740 84
1788279745 82
1788279750 82
1788279755 82
1788279760 82
1788279765 82
1788279770 82
1788279775 82
1788279780 82
```
</details>

---

