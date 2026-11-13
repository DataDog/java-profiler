---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:34:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 25-32 cores)</summary>

```
1794587404 25
1794587409 25
1794587414 25
1794587419 25
1794587424 25
1794587429 25
1794587434 25
1794587439 25
1794587444 25
1794587449 32
1794587454 32
1794587459 32
1794587464 32
1794587469 25
1794587474 25
1794587479 25
1794587484 25
1794587489 25
1794587494 25
1794587499 25
```
</details>

---

