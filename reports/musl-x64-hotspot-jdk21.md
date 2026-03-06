---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-06 04:35:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 12 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (6 unique values: 38-59 cores)</summary>

```
1772789454 59
1772789459 59
1772789464 54
1772789469 54
1772789474 54
1772789479 54
1772789484 54
1772789489 50
1772789494 50
1772789499 42
1772789504 42
1772789509 40
1772789514 40
1772789519 42
1772789524 42
1772789529 42
1772789534 42
1772789539 38
1772789544 38
1772789549 38
```
</details>

---

