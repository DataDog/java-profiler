---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 06:25:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1794914454 77
1794914459 77
1794914464 77
1794914469 77
1794914474 79
1794914479 79
1794914484 79
1794914489 79
1794914494 79
1794914499 79
1794914504 81
1794914509 81
1794914514 81
1794914519 81
1794914524 81
1794914529 81
1794914534 81
1794914539 81
1794914544 81
1794914549 81
```
</details>

---

