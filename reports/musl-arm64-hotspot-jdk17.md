---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 10:25:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 9 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (4 unique values: 40-48 cores)</summary>

```
1795706424 40
1795706429 40
1795706434 40
1795706439 40
1795706444 40
1795706449 40
1795706454 40
1795706459 40
1795706464 40
1795706469 40
1795706474 44
1795706479 44
1795706484 44
1795706489 44
1795706495 44
1795706500 44
1795706505 48
1795706510 48
1795706515 48
1795706520 48
```
</details>

---

