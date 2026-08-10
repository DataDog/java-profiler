---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 06:45:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 37-70 cores)</summary>

```
1786358496 37
1786358501 37
1786358506 37
1786358511 37
1786358516 37
1786358521 70
1786358526 70
1786358531 44
1786358536 44
1786358541 44
1786358546 44
1786358551 44
1786358556 44
1786358561 44
1786358566 44
1786358571 44
1786358576 44
1786358581 44
1786358586 44
1786358591 44
```
</details>

---

