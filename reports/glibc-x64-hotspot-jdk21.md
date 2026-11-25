---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 05:33:19 EST

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 8 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 21-32 cores)</summary>

```
1795602444 21
1795602449 21
1795602454 21
1795602459 30
1795602464 30
1795602469 30
1795602474 30
1795602479 30
1795602484 30
1795602489 30
1795602494 30
1795602499 30
1795602504 30
1795602509 32
1795602514 32
1795602519 32
1795602524 32
1795602529 32
1795602534 32
1795602539 32
```
</details>

---

