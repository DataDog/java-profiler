---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-29 08:24:19 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 9 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 49-81 cores)</summary>

```
1790684418 79
1790684423 79
1790684428 79
1790684433 81
1790684438 81
1790684443 81
1790684448 81
1790684453 81
1790684458 81
1790684463 81
1790684468 81
1790684474 51
1790684479 51
1790684484 51
1790684489 49
1790684494 49
1790684499 49
1790684504 49
1790684509 49
1790684514 49
```
</details>

---

