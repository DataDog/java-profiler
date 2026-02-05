---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-05 15:03:47 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 11 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 13 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (5 unique values: 71-80 cores)</summary>

```
1770321464 77
1770321469 77
1770321474 77
1770321479 77
1770321484 80
1770321489 80
1770321494 80
1770321499 80
1770321504 80
1770321509 75
1770321514 75
1770321519 75
1770321524 75
1770321529 75
1770321534 73
1770321539 73
1770321544 73
1770321549 73
1770321554 73
1770321559 73
```
</details>

---

