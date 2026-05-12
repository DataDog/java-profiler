---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:45:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 436 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 52-55 cores)</summary>

```
1778582444 52
1778582449 52
1778582454 52
1778582459 52
1778582464 52
1778582469 52
1778582474 52
1778582479 52
1778582484 52
1778582489 55
1778582494 55
1778582499 55
1778582504 55
1778582509 55
1778582514 55
1778582519 55
1778582524 55
1778582529 55
1778582534 55
1778582539 55
```
</details>

---

