---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 06:46:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 853 |
| Sample Rate | 14.22/sec |
| Health Score | 889% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 55-87 cores)</summary>

```
1778582409 55
1778582414 55
1778582419 55
1778582424 60
1778582429 60
1778582434 60
1778582439 60
1778582444 60
1778582449 60
1778582454 60
1778582459 60
1778582464 60
1778582469 60
1778582474 60
1778582479 60
1778582484 60
1778582489 60
1778582494 60
1778582499 60
1778582504 78
```
</details>

---

