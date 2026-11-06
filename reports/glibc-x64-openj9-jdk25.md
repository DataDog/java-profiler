---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 14:19:16 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 10 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 81-89 cores)</summary>

```
1793992454 81
1793992459 81
1793992464 81
1793992469 81
1793992474 87
1793992479 87
1793992484 87
1793992489 87
1793992494 87
1793992499 89
1793992504 89
1793992509 89
1793992514 89
1793992519 89
1793992524 89
1793992529 89
1793992534 89
1793992539 89
1793992544 89
1793992549 89
```
</details>

---

