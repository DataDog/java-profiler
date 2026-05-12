---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-12 06:45:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778582454 64
1778582459 64
1778582464 64
1778582469 64
1778582474 64
1778582479 64
1778582484 64
1778582489 64
1778582494 64
1778582499 64
1778582504 64
1778582509 64
1778582514 64
1778582519 64
1778582524 64
1778582529 64
1778582534 64
1778582540 64
1778582545 64
1778582550 64
```
</details>

---

