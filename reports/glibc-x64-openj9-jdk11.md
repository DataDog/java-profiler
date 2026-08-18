---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 13:40:53 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 76-96 cores)</summary>

```
1787074523 94
1787074528 94
1787074533 94
1787074538 94
1787074543 94
1787074548 94
1787074553 94
1787074558 94
1787074563 94
1787074568 96
1787074573 96
1787074578 96
1787074583 96
1787074588 76
1787074593 76
1787074598 76
1787074603 76
1787074608 76
1787074613 76
1787074618 76
```
</details>

---

