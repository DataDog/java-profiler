---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-06 04:35:42 EST

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
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 56-92 cores)</summary>

```
1772789453 87
1772789458 87
1772789463 92
1772789468 92
1772789473 92
1772789478 92
1772789483 92
1772789488 92
1772789493 92
1772789498 92
1772789503 92
1772789508 92
1772789513 92
1772789518 92
1772789523 92
1772789528 92
1772789533 92
1772789538 92
1772789543 92
1772789548 56
```
</details>

---

