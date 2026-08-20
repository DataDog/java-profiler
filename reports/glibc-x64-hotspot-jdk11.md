---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 09:32:07 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 970 |
| Sample Rate | 16.17/sec |
| Health Score | 1011% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 60-68 cores)</summary>

```
1787232429 68
1787232434 68
1787232439 68
1787232444 68
1787232449 68
1787232454 68
1787232459 68
1787232464 68
1787232469 68
1787232474 68
1787232479 60
1787232484 60
1787232489 60
1787232494 60
1787232499 60
1787232504 60
1787232509 60
1787232514 60
1787232519 60
1787232524 60
```
</details>

---

