---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-21 20:15:08 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1787357488 79
1787357493 79
1787357498 81
1787357503 81
1787357508 81
1787357513 81
1787357518 81
1787357523 81
1787357528 79
1787357533 79
1787357538 79
1787357543 79
1787357548 79
1787357553 79
1787357558 79
1787357563 79
1787357568 79
1787357573 81
1787357578 81
1787357583 81
```
</details>

---

