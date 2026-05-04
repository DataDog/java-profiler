---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-03 21:22:14 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 8 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1777857416 58
1777857421 58
1777857426 58
1777857431 58
1777857436 58
1777857441 58
1777857446 58
1777857451 58
1777857457 58
1777857462 58
1777857467 58
1777857472 58
1777857477 58
1777857482 56
1777857487 56
1777857492 56
1777857497 56
1777857502 56
1777857507 56
1777857512 56
```
</details>

---

