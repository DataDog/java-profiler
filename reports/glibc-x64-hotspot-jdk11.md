---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-05 08:26:01 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (5 unique values: 54-74 cores)</summary>

```
1785932436 74
1785932441 74
1785932446 72
1785932451 72
1785932456 74
1785932461 74
1785932466 74
1785932471 66
1785932476 66
1785932481 66
1785932486 66
1785932491 66
1785932496 66
1785932501 66
1785932506 66
1785932511 66
1785932516 66
1785932521 56
1785932526 56
1785932531 56
```
</details>

---

