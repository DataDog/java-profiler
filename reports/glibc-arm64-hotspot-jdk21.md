---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 00:59:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 9 |
| Allocations | 110 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 13 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790830525 43
1790830530 43
1790830535 48
1790830540 48
1790830545 48
1790830550 48
1790830555 48
1790830560 48
1790830565 48
1790830570 48
1790830575 48
1790830580 48
1790830585 48
1790830590 48
1790830595 48
1790830600 48
1790830605 48
1790830610 48
1790830615 48
1790830620 48
```
</details>

---

