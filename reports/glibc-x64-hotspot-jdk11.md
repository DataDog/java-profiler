---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-19 00:58:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 8 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1789793656 90
1789793661 90
1789793666 90
1789793671 90
1789793676 90
1789793681 90
1789793686 90
1789793691 90
1789793696 92
1789793701 92
1789793706 92
1789793711 92
1789793716 92
1789793721 92
1789793726 96
1789793731 96
1789793736 96
1789793741 96
1789793746 96
1789793751 96
```
</details>

---

