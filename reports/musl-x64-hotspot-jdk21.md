---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-26 01:03:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 876 |
| Sample Rate | 14.60/sec |
| Health Score | 912% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (5 unique values: 55-96 cores)</summary>

```
1790398403 57
1790398408 59
1790398413 59
1790398418 59
1790398423 59
1790398428 59
1790398433 59
1790398438 57
1790398443 57
1790398448 55
1790398454 55
1790398459 55
1790398464 55
1790398469 57
1790398474 57
1790398479 57
1790398484 57
1790398489 94
1790398494 94
1790398499 96
```
</details>

---

