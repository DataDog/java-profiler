---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-06 10:08:48 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 12 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 68-75 cores)</summary>

```
1791295373 75
1791295378 75
1791295383 75
1791295388 70
1791295393 70
1791295398 68
1791295403 68
1791295408 68
1791295413 68
1791295418 68
1791295423 70
1791295428 70
1791295433 70
1791295438 70
1791295443 70
1791295448 70
1791295453 73
1791295458 73
1791295463 73
1791295468 73
```
</details>

---

