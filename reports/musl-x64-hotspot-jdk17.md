---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 05:26:31 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 860 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 55-75 cores)</summary>

```
1789982415 75
1789982420 75
1789982425 75
1789982430 75
1789982435 75
1789982440 75
1789982445 75
1789982450 75
1789982455 75
1789982460 65
1789982465 65
1789982470 65
1789982475 65
1789982480 65
1789982485 65
1789982490 65
1789982495 65
1789982500 55
1789982505 55
1789982510 55
```
</details>

---

