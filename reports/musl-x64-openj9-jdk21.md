---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-06 04:35:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 19-30 cores)</summary>

```
1772789433 19
1772789438 19
1772789443 19
1772789448 19
1772789453 19
1772789458 19
1772789463 19
1772789468 19
1772789473 19
1772789478 21
1772789483 21
1772789488 21
1772789493 21
1772789498 21
1772789503 21
1772789508 25
1772789513 25
1772789518 25
1772789523 25
1772789528 25
```
</details>

---

