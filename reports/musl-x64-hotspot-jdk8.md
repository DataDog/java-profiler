---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-02-03 11:55:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1770137455 28
1770137460 28
1770137465 28
1770137470 30
1770137475 30
1770137480 30
1770137485 30
1770137490 30
1770137495 30
1770137500 30
1770137505 30
1770137510 30
1770137515 30
1770137520 30
1770137525 30
1770137530 30
1770137535 30
1770137540 30
1770137545 30
1770137550 30
```
</details>

---

