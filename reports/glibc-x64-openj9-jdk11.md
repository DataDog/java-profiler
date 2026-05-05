---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-05 08:22:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 809 |
| Sample Rate | 13.48/sec |
| Health Score | 842% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 35-48 cores)</summary>

```
1777983529 35
1777983534 35
1777983539 35
1777983544 35
1777983549 40
1777983554 40
1777983559 35
1777983564 35
1777983569 35
1777983574 35
1777983579 35
1777983584 35
1777983589 44
1777983594 44
1777983599 44
1777983604 48
1777983609 48
1777983614 48
1777983619 48
1777983624 48
```
</details>

---

