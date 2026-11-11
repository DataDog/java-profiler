---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 19:10:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 90-92 cores)</summary>

```
1794355414 90
1794355419 90
1794355424 90
1794355429 90
1794355434 90
1794355439 90
1794355444 90
1794355449 90
1794355454 90
1794355459 90
1794355464 90
1794355469 90
1794355474 90
1794355479 90
1794355484 90
1794355489 90
1794355494 92
1794355499 92
1794355504 92
1794355509 92
```
</details>

---

