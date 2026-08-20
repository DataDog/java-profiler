---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-20 13:25:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1787246439 32
1787246444 32
1787246449 32
1787246454 32
1787246459 32
1787246464 32
1787246469 32
1787246474 32
1787246479 32
1787246484 32
1787246489 32
1787246494 32
1787246499 32
1787246504 32
1787246509 32
1787246514 32
1787246519 32
1787246524 32
1787246529 32
1787246534 32
```
</details>

---

