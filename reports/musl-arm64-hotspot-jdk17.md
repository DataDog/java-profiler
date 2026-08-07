---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 08:27:33 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 11 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 336 |
| Sample Rate | 5.60/sec |
| Health Score | 350% |
| Threads | 14 |
| Allocations | 106 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1786105425 46
1786105430 46
1786105435 46
1786105440 46
1786105445 46
1786105450 46
1786105455 51
1786105460 51
1786105465 51
1786105470 51
1786105475 51
1786105480 51
1786105485 51
1786105490 51
1786105495 51
1786105500 51
1786105505 51
1786105510 51
1786105515 51
1786105520 51
```
</details>

---

