---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:02:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 10 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 55-63 cores)</summary>

```
1794405468 57
1794405473 57
1794405478 57
1794405483 57
1794405488 57
1794405493 57
1794405498 57
1794405503 57
1794405508 57
1794405513 57
1794405518 55
1794405523 55
1794405528 63
1794405533 63
1794405538 63
1794405543 63
1794405548 63
1794405553 63
1794405558 63
1794405563 63
```
</details>

---

