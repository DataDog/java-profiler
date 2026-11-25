---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 08:37:25 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (4 unique values: 42-64 cores)</summary>

```
1795613507 47
1795613512 42
1795613518 42
1795613523 42
1795613528 42
1795613533 42
1795613538 42
1795613543 42
1795613548 42
1795613553 59
1795613558 59
1795613563 59
1795613568 59
1795613573 64
1795613578 64
1795613583 64
1795613588 64
1795613593 64
1795613598 64
1795613603 64
```
</details>

---

