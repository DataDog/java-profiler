---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:46:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1052 |
| Sample Rate | 17.53/sec |
| Health Score | 1096% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 22-35 cores)</summary>

```
1778582424 22
1778582429 22
1778582434 22
1778582439 22
1778582444 22
1778582449 22
1778582454 22
1778582459 22
1778582464 22
1778582469 22
1778582474 22
1778582479 22
1778582484 22
1778582489 22
1778582494 22
1778582499 22
1778582504 31
1778582509 31
1778582514 31
1778582519 31
```
</details>

---

