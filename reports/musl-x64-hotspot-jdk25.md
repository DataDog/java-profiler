---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 05:55:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 22-28 cores)</summary>

```
1791539315 22
1791539320 22
1791539325 24
1791539330 24
1791539335 24
1791539340 24
1791539345 26
1791539350 26
1791539355 26
1791539360 26
1791539365 26
1791539370 26
1791539375 26
1791539380 26
1791539385 28
1791539390 28
1791539395 28
1791539400 28
1791539405 28
1791539410 28
```
</details>

---

