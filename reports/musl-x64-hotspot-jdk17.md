---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 06:23:10 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 81-85 cores)</summary>

```
1795605436 83
1795605441 85
1795605446 85
1795605451 85
1795605456 85
1795605461 85
1795605466 85
1795605471 81
1795605476 81
1795605481 81
1795605486 81
1795605491 81
1795605496 81
1795605501 81
1795605506 81
1795605511 81
1795605516 81
1795605521 81
1795605526 81
1795605531 81
```
</details>

---

