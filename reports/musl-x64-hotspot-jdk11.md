---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 07:21:19 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 65-88 cores)</summary>

```
1789989425 76
1789989430 76
1789989435 78
1789989440 78
1789989445 78
1789989450 78
1789989455 78
1789989460 78
1789989465 78
1789989470 78
1789989475 78
1789989480 78
1789989485 88
1789989490 88
1789989495 88
1789989500 88
1789989505 88
1789989510 88
1789989515 88
1789989520 88
```
</details>

---

