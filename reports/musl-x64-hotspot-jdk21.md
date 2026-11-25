---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:28:02 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 12 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 81-87 cores)</summary>

```
1795627387 81
1795627392 81
1795627397 81
1795627402 81
1795627407 81
1795627412 81
1795627417 81
1795627422 81
1795627427 81
1795627432 81
1795627437 81
1795627442 81
1795627447 81
1795627452 81
1795627457 87
1795627462 87
1795627467 87
1795627472 87
1795627477 87
1795627482 87
```
</details>

---

