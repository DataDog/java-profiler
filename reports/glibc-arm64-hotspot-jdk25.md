---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-06 08:29:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 26-36 cores)</summary>

```
1791289525 36
1791289530 36
1791289535 36
1791289540 36
1791289545 36
1791289550 36
1791289555 36
1791289560 36
1791289565 36
1791289570 36
1791289575 36
1791289580 36
1791289585 36
1791289590 36
1791289595 36
1791289600 36
1791289605 36
1791289610 36
1791289615 36
1791289620 31
```
</details>

---

