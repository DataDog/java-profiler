---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 11:31:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795105570 59
1795105575 59
1795105580 59
1795105585 59
1795105590 64
1795105595 64
1795105600 64
1795105605 64
1795105610 64
1795105615 64
1795105620 64
1795105625 64
1795105630 64
1795105635 64
1795105640 64
1795105645 64
1795105650 64
1795105655 64
1795105660 64
1795105665 64
```
</details>

---

