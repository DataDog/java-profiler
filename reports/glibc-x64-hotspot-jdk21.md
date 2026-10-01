---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 07:23:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 68-70 cores)</summary>

```
1790853540 68
1790853545 68
1790853550 70
1790853555 70
1790853560 70
1790853565 70
1790853570 70
1790853575 70
1790853580 70
1790853585 70
1790853590 70
1790853595 70
1790853600 70
1790853605 70
1790853610 70
1790853615 70
1790853620 70
1790853625 70
1790853630 70
1790853635 70
```
</details>

---

