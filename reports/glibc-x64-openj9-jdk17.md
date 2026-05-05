---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-05 08:22:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 68-80 cores)</summary>

```
1777983479 75
1777983484 75
1777983489 75
1777983494 75
1777983499 75
1777983504 80
1777983509 80
1777983514 80
1777983519 80
1777983524 80
1777983529 80
1777983534 80
1777983539 80
1777983544 80
1777983549 80
1777983554 80
1777983559 80
1777983564 80
1777983569 80
1777983574 80
```
</details>

---

