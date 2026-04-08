---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-08 12:51:00 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1016 |
| Sample Rate | 16.93/sec |
| Health Score | 1058% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 79-86 cores)</summary>

```
1775666675 86
1775666680 86
1775666685 86
1775666690 79
1775666695 79
1775666700 79
1775666705 79
1775666710 79
1775666715 83
1775666720 83
1775666725 83
1775666730 83
1775666735 83
1775666740 83
1775666745 83
1775666750 83
1775666755 83
1775666760 83
1775666765 83
1775666770 83
```
</details>

---

